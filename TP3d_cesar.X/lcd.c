/* LCD Explorer 8 (PIC16F1719) */

#include <xc.h>
#include "lcd.h"
#include "spi.h"

#define _XTAL_FREQ 8000000
#define LCD_CHIP_SELECT      LATAbits.LATA2
#define LCD_CHIP_SELECT_TRIS TRISAbits.TRISA2

#define LCD_CLEAR               0x01
#define LCD_VDD_EN              0x20
#define LCD_FUNCTION_SET        0x3C
#define LCD_SET_DISPLAY         0x0C
#define LCD_SET_DDRAM_ADDRESS   0x80
#define LINE1_START_ADDRESS     0x80
#define LINE2_START_ADDRESS     0xC0
#define OUTPUT_DIR              0x00

void LCD_InitializePins(void){
    LCD_CHIP_SELECT      = 1; // Init high (active low)
    LCD_CHIP_SELECT_TRIS = 0; // Output
}

void LCD_Initialize(void) {
    LCD_WriteIOExpander(IO_DIR_A_ADDRESS, OUTPUT_DIR);
    LCD_WriteIOExpander(IO_DIR_B_ADDRESS, OUTPUT_DIR);
    LCD_WriteIOExpander(GPIO_A_ADDRESS, LCD_VDD_EN);
    __delay_ms(10);
    LCD_WriteCommand(LCD_FUNCTION_SET);
    __delay_ms(10);
    LCD_WriteCommand(LCD_SET_DISPLAY);
    __delay_ms(10);
    LCD_WriteCommand(LCD_CLEAR);
    __delay_ms(10);
    LCD_WriteCommand(LCD_SET_DISPLAY);
    __delay_ms(130);
    LCD_WriteCommand(LCD_SET_DDRAM_ADDRESS);
    __delay_ms(1);
}

void LCD_WriteIOExpander(char reg, char data) {
    LCD_CHIP_SELECT = 0;
    SPI_Exchange8bit(IO_EXPD_ADDRESS);
    SPI_Exchange8bit(reg);
    SPI_Exchange8bit(data);
    LCD_CHIP_SELECT = 1;
}

void LCD_WriteCommand(char cmd) {
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0x60);  // RS=0, E=1
    LCD_WriteIOExpander(GPIO_B_ADDRESS, cmd);
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0x20);  // RS=0, E=0
}

void LCD_WriteByte(char data) {
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0xE0);  // RS=1, E=1
    LCD_WriteIOExpander(GPIO_B_ADDRESS, data);
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0xA0);  // RS=1, E=0
}

void LCD_WriteString(const char *data) {
    char i = 0;
    while (data[i]) {
        LCD_WriteByte(data[i++]);
    }
}

void LCD_GoTo(char row, char column) {
    if (row < 2) {
        char pos = (row == 0) ? (LINE1_START_ADDRESS | column) : (LINE2_START_ADDRESS | column);
        LCD_WriteCommand(pos);
    }
}

void LCD_Clear(void) {
    LCD_WriteCommand(LCD_CLEAR);
    LCD_GoTo(0, 0);
}

// Wrappers simples (noms en minuscules)
void lcd_init(void)
{
    SPI_InitializePins();
    SPI_Initialize();
    LCD_InitializePins();
    LCD_Initialize();
}

void lcd_clear(void)
{
    LCD_Clear();
}

void lcd_goto(unsigned char row, unsigned char col)
{
    LCD_GoTo((char)row, (char)col);
}

void lcd_write_string(const char *s)
{
    LCD_WriteString(s);
}
