#include "configbits.h"
#include <xc.h>
#include <stdint.h>

#include "adc.h"
#include "uart.h"
#include "caesar.h"
#include "lcd.h"

// Fréquence d'horloge pour __delay_ms()
#define _XTAL_FREQ 8000000UL

// Variables partagées entre le main et l'interruption
// Mode => 0 = chiffrement, 1 = dechiffrement
static volatile uint8_t g_decrypt = 0;
// Décalage César 
static volatile uint8_t g_offset = 0;

// Routine d'interruption 
void __interrupt() isr(void)
{
    // Interruption réception UART 
    if (PIR1bits.RCIF)
    {
       // Lecture du caractère reçu 
        uint8_t c = RC1REG;

        // Transformation César selon offset 
        uint8_t out = caesar_transform(c, g_offset, g_decrypt);

        // Renvoie le caractère transformé sur l'UART 
        uart_write(out);
    }
}

// Initialisation du bouton sur RB0
static void button_init(void)
{
    // RB0 en numérique 
    ANSELBbits.ANSB0 = 0;

    // RB0 en entrée
    TRISBbits.TRISB0 = 1;

    // Activation des pull-ups faibles sur PORTB
    // S1 est câblé actif bas : sans appui, le pull-up met RB0 à 1
    OPTION_REGbits.nWPUEN = 0;
    WPUBbits.WPUB0 = 1;
}

// Retourne 1 si le bouton est appuyé
static uint8_t button_pressed(void)
{
    // S1 bouton appuyé => RB0 = 0
    return (PORTBbits.RB0 == 0);
}

// Écrit v sur 2 caractères (ex: 7 -> "07", 35 -> "35")
static void write_2digits(char *dst, uint8_t v)
{
    dst[0] = (char)('0' + (v / 10)); // dizaine
    dst[1] = (char)('0' + (v % 10)); // unité
}

// Met à jour l'affichage LCD : mode + offset
static void lcd_update(uint8_t offset, uint8_t decrypt)
{
    char line1[17];                 // 16 caractères + '\0'
    char line2[17] = "Offset: 00      "; // texte de base ligne 2

    // Affiche le mode sur 16 caractères
    if (decrypt)
    {
        const char *s = "Mode: Dechiffre ";
        for (uint8_t i = 0; i < 16; i++) line1[i] = s[i];
    }
    else
    {
        const char *s = "Mode: Chiffre   ";
        for (uint8_t i = 0; i < 16; i++) line1[i] = s[i];
    }
    line1[16] = '\0'; // fin de chaîne

   //Met à jour les 2 chiffres de l'offset
  
    write_2digits(&line2[8], offset);
    line2[16] = '\0'; // fin de chaîne

    // Envoi au LCD
    lcd_clear(); //On efface l'écran LCD
    lcd_goto(0, 0); //On va à la ligne du haut tout à gauche
    lcd_write_string(line1); //On écrit la ligne 1 (Chifferement ou déchiffrement)
    lcd_goto(1, 0); //On va à la ligne en-dessous, la ligne basse du LCD et tout à gauche
    lcd_write_string(line2); //On écrit la ligne 2 (l'offset)
}

int main(void)
{
    // Initialisations des périphériques
    uart_init();
    adc_init();
    button_init();
    lcd_init();

    // Activation des interruptions UART RX 
    PIR1bits.RCIF = 0;  // efface le flag RX
    PIE1bits.RCIE = 1;  // autorise l'interruption RX
    INTCONbits.PEIE = 1; // interruptions périphériques
    INTCONbits.GIE  = 1; // interruptions globales

    // Permet d'éviter de rafraîchir le LCD si rien n'a changé
    uint8_t last_offset = 0xFF;
    uint8_t last_mode   = 0xFF;

    while (1)
    {
        // Lecture du potentiomètre :
        // ADC 10 bits => 0..1023
        // Conversion vers offset 0..35
        uint16_t adc = adc_read();
        uint8_t offset = (uint8_t)((adc * 36U) / 1024U);

        // Bouton S1 permet la bascule entre le chiffrement et le déchiffrement
        if (button_pressed())
        {
            __delay_ms(20); // anti-rebond permet d'être sur que l'appuie était volontaire 

            if (button_pressed())
            {
                // Change le mode entre chiffrement et déchiffrement 
                g_decrypt = (uint8_t)!g_decrypt;

                // Attend que le bouton soit relâcher pour éviter plusieurs bascules
                while (button_pressed()){};
            }
        }

        // Met à jour l'offset utilisé par l'interruption UART
        g_offset = offset;

        // Met à jour le LCD uniquement si le mode ou l'offset a changé
        if (offset != last_offset || g_decrypt != last_mode)
        {
            lcd_update(offset, g_decrypt);
            last_offset = offset;
            last_mode = g_decrypt;
        }
    }

    return 0; // (en pratique jamais atteint)
}
