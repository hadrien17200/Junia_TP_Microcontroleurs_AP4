#include "configbits.h"   // Bits de configuration du microcontrôleur
#include <xc.h>           // Bibliothèque principale XC8
#include <stdint.h>       // Types entiers standard (uint8_t, etc.)

#define _XTAL_FREQ 8000000UL   // Fréquence de l'oscillateur (8 MHz), nécessaire pour __delay_ms()
#define tx_delay __delay_ms(2) // Délai entre chaque caractère envoyé (2 ms)

void main(void)
{
    // Configuration du Peripheral Pin Select (PPS)
    RC6PPS = 0b10100;  // Associe RC6 à la sortie TX
    RXPPS  = 0b10111;  // Associe RC7 à l'entrée RX

    // Désactivation du mode analogique sur le port C
    ANSELC = 0;        // Tous les pins du port C en numérique

    // Configuration des directions des broches
    TRISCbits.TRISC6 = 0; // RC6 configurée en sortie (TX)
    TRISCbits.TRISC7 = 1; // RC7 configurée en entrée (RX)
    
    // Configuration du module UART
    TX1STA = 0b00100000;  // TXEN = 1 activation de l'émetteur
                          // Asynchrone, 8 bits, vitesse normale
    RC1STA = 0b10010000;  // SPEN = 1 activation du port série
                          // CREN = 1 activation de la réception continue

    // Configuration du baud rate
    SP1BRGL = 12;         // Valeur basse du générateur de baud rate
    SP1BRGH = 0;          // Valeur haute (baud rate  9600 bps à 8 MHz)
  
    while (1)
    {
        // Envoi de la chaîne "Hello World !"
        TX1REG = 'H'; tx_delay;
        TX1REG = 'e'; tx_delay;
        TX1REG = 'l'; tx_delay;
        TX1REG = 'l'; tx_delay;
        TX1REG = 'o'; tx_delay; 
        TX1REG = ' '; tx_delay;
        TX1REG = 'W'; tx_delay;
        TX1REG = 'o'; tx_delay;
        TX1REG = 'r'; tx_delay;
        TX1REG = 'l'; tx_delay;
        TX1REG = 'd'; tx_delay;
        TX1REG = ' '; tx_delay;
        TX1REG = '!'; tx_delay;

        // Retour à la ligne
        TX1REG = '\n'; tx_delay;  // Nouvelle ligne
        TX1REG = '\r'; tx_delay;  // Retour chariot 
    }
}
