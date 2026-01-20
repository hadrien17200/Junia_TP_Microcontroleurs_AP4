#include "configbits.h"
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000

void config_leds(void)
{
    ANSELB = 0;          // Port B en numérique
    ANSELD = 0;          // Port D en numérique

    TRISB = 0xF0;        // RB0..RB3 en sortie
    TRISD = 0xF0;        // RD0..RD3 en sortie

    LATB = 0;            // LEDs éteintes
    LATD = 0;           // LEDs éteintes
}


   //Configuration ADC sur AN0 (RA0)

void config_adc(void)
{
    TRISAbits.TRISA0 = 1;    // RA0 en entrée
    ANSELAbits.ANSA0 = 1;    // RA0 en analogique

    ADCON1 = 0b10000000;    // Résultat justifié à droite
    ADCON0 = 0b00000001;    // AN0 sélectionné + ADC activé
}


//   Lecture de l?ADC (0 à 1023)

uint16_t lire_adc(void)
{
    ADCON0bits.GO = 1;          // Lancer conversion
    while (ADCON0bits.GO);      // Attendre fin

    return ((uint16_t)ADRESH << 8) | ADRESL;
}

void main(void)
{
    uint16_t valeur_adc;
    uint8_t led;

    config_leds();
    config_adc();

    while (1)
    {
        valeur_adc = lire_adc();     // Lecture potentiomètre

        led = valeur_adc / 128;      // 0..1023 ? 0..7

        LATB = 0;                    // Éteindre LEDs
        LATD = 0;

        if (led < 4)
            LATD = (1 << led);       // D1 à D4
        else
            LATB = (1 << (led - 4)); // D5 à D8
    }
}
