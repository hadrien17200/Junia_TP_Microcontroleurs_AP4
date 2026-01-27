#include "configbits.h"
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000UL
#define tx_delay __delay_ms(2) // Délai entre chaque caractère envoyé (2 ms)


void __interrupt() isr(void) //  interruption 
{
    // Vérifie si l'interruption provient de la réception UART
    // RCIF = 1 lorsqu'un caractère est reçu dans RC1REG
    if (PIR1bits.RCIF)
    {
        // On attend que le registre d'émission soit disponible
        // TXIF = 1 signifie que TX1REG est vide et prêt à recevoir une donnée
        while (!PIR1bits.TXIF){};

        // Lecture du caractère reçu dans RC1REG
        // (cette lecture efface automatiquement le flag RCIF)
        // Donc on le renvoi directement sur la liaison UART (echo)
        TX1REG = RC1REG;
    }
}


void main(void)
{

    RC6PPS = 0b10100;   // RC6 = TX
    RXPPS  = 0b10111;   // RC7 = RX

    // --- I/O ---
    ANSELC = 0;                 // Port C en numérique
    TRISCbits.TRISC6 = 0;       // TX en sortie
    TRISCbits.TRISC7 = 1;       // RX en entrée

    // Configuration du module UART
    TX1STA = 0b00100000;  // TXEN = 1 activation de l'émetteur
                          // Asynchrone, 8 bits, vitesse normale
    RC1STA = 0b10010000;  // SPEN = 1 activation du port série
                          // CREN = 1 activation de la réception continue

     // Configuration du baud rate
    SP1BRGL = 12;         // Valeur basse du générateur de baud rate
    SP1BRGH = 0;          // Valeur haute (baud rate 9600 bps à 8 MHz)

    // --- Interruptions UART RX ---
    PIR1bits.RCIF = 0;          // clear du flag RX
    PIE1bits.RCIE = 1;          // autoriser l'interruption de réception (RCIE)
    INTCONbits.PEIE = 1;        // interruptions périphériques
    INTCONbits.GIE  = 1;        // interruptions globales

    while (1)
    {
        //L?écho est géré dans interruption
    }
}
