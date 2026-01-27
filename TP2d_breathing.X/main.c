#include "configbits.h"
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000UL

// Variables globales utilisées dans l'interruption 
volatile uint16_t rapport = 0;   // Rapport cyclique (0 à 1000 environ)
volatile uint8_t sens = 1;       // 1 = on augmente, 0 = on diminue

// Met le rapport cyclique PWM4 (sur 10 bits)
void pwm4_rapport(uint16_t val)
{
    if (val > 1023) val = 1023;          // sécurité

    PWM4DCH = (uint8_t)(val >> 2);       // 8 bits forts
    PWM4DCL = (uint8_t)((val & 3) << 6); // 2 bits faibles
}

void main(void)
{
    // LED D1 sur RD0 
    ANSELD = 0;                 // Port D en numérique 
    TRISDbits.TRISD0 = 0;       // RD0 en sortie
    LATDbits.LATD0 = 0;         // LED éteinte au départ
    RD0PPS = 0x0F;              // PWM4 connecté à RD0

    //Timer2 (base PWM + interruption) 
    PR2 = 249;                  // Période (donne environ 2 ms par interruption)
    T2CONbits.T2CKPS = 0b10;    // Prescaler 1:16
    T2CONbits.TMR2ON = 1;       // Timer2 ON

    // PWM4
    PWM4CONbits.PWM4POL = 0;    // Polarité normale
    PWM4CONbits.PWM4EN  = 1;    // PWM4 ON
    pwm4_rapport(0);            // départ à 0% (LED éteinte)

    // Interruptions Timer2 
    PIR1bits.TMR2IF = 0;        // effacer le drapeau
    PIE1bits.TMR2IE = 1;        // autoriser l'interruption Timer2
    INTCONbits.PEIE = 1;        // interruptions périphériques
    INTCONbits.GIE  = 1;        // interruptions globales

    while (1)
    {
        // breathing  géré dans l'interruption
    }
}

//Routine d'interruption 
void __interrupt() isr(void)
{
    if (PIR1bits.TMR2IF)          //interruption Timer2
    {
        PIR1bits.TMR2IF = 0;      // effacer le drapeau

        if (sens == 1)
        {
            // On augmente la luminosité
            rapport += 2;

            if (rapport >= 1000)  // arrivé en haut
            {
                rapport = 1000;
                sens = 0;         // on change de sens  vers la descente
            }
        }
        else
        {
            // On diminue la luminosité
            if (rapport > 2) 
            {
                rapport -= 2;
            }
            else rapport = 0;

            if (rapport == 0)     // arrivé en bas
            {
                sens = 1;         // on change de sens vers la montée
            }
        }

        pwm4_rapport(rapport);    // mettre à jour le PWM
    }
}
