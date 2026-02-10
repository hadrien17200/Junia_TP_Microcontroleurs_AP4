/* LCD Explorer 8 (PIC16F1719) */


#ifndef LCD_H
#define	LCD_H

#define IO_EXPD_ADDRESS     0x40  
#define GPIO_A_ADDRESS      0x12
#define GPIO_B_ADDRESS      0x13
#define IO_DIR_A_ADDRESS    0x00
#define IO_DIR_B_ADDRESS    0x01

void LCD_InitializePins(void);
void LCD_Initialize(void);
void LCD_WriteIOExpander(char reg, char data);
void LCD_WriteCommand(char cmd);
void LCD_WriteByte(char data);
void LCD_WriteString(const char *data);
void LCD_GoTo(char row, char column);
void LCD_Clear(void);

// Wrappers simples (noms en minuscules)
void lcd_init(void);
void lcd_clear(void);
void lcd_goto(unsigned char row, unsigned char col);
void lcd_write_string(const char *s);

#endif	/* LCD_H */
