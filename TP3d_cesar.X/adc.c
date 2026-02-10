#include <xc.h>
#include <stdint.h>
#include "adc.h"

void adc_init(void)
{
    // ADC sur AN0 (RA0)
    TRISAbits.TRISA0 = 1;      // RA0 en entrée
    ANSELAbits.ANSA0 = 1;      // RA0 en analogique

    ADCON1bits.ADPREF = 0;     // Vref+ = VDD
    ADCON1bits.ADNREF = 0;     // Vref- = VSS
    ADCON1bits.ADFM   = 1;     // Resultat a droite
    ADCON1bits.ADCS  = 0b110;  // Horloge ADC

    ADCON0bits.CHS  = 0;       // Canal AN0
    ADCON0bits.ADON = 1;       // ADC actif
}

uint16_t adc_read(void)
{
    ADCON0bits.GO = 1;// Lance une conversion analogique ? numérique
    
    while (ADCON0bits.GO);// Attend la fin de la conversion, attend que GO repasse à zéro
    
    
    // Récupère le résultat sur 16 bits :
    // ADRESH contient les bits de poids fort
    // ADRESL contient les bits de poids faible
    // On décale ADRESH de 8 bits puis on assemble les deux registres
    return (uint16_t)(((uint16_t)ADRESH << 8) | ADRESL);
}
