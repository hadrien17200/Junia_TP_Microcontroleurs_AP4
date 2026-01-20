#include "configbits.h"
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000

void main(void)
{
    uint16_t adc;   // Valeur du potentiomètre (0 à 1023)

    //CONFIGURATION ADC 

    TRISAbits.TRISA0 = 1;      // RA0 en entrée
    ANSELAbits.ANSA0 = 1;      // RA0 en analogique

    ADCON1bits.ADPREF = 0;     // Vref+ = VDD
    ADCON1bits.ADNREF = 0;     // Vref- = VSS
    ADCON1bits.ADFM   = 1;     // Résultat justifié à droite
    ADCON1bits.ADCS  = 0b110;  // Horloge ADC

    ADCON0bits.CHS  = 0;       // Canal AN0
    ADCON0bits.ADON = 1;       // ADC activé

   //CONFIGURATION PWM 

    PR2 = 249;                 // Période PWM
    T2CONbits.T2CKPS = 0b10;   // Prescaler 1:16
    T2CONbits.TMR2ON = 1;      // Timer2 ON

    PWM4CONbits.PWM4POL = 0;   // Polarité normale
    PWM4CONbits.PWM4EN  = 1;   // PWM4 ON

    //LED D1 (RD0)

    ANSELD = 0;                // Port D en numérique
    TRISDbits.TRISD0 = 0;      // RD0 en sortie
    RD0PPS = 0x0F;             // PWM4 connecté à RD0


    while (1)
    {
        /* Lancer conversion ADC */
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO);     // Attendre fin conversion

        /* Lire valeur ADC (0 à 1023) */
        adc = ((uint16_t)ADRESH << 8) | ADRESL;

        /* Utiliser directement l?ADC comme rapport cyclique */
        PWM4DCH = adc >> 2;            // 8 bits forts
        PWM4DCL = (adc & 0x03) << 6;   // 2 bits faibles
    }
}
