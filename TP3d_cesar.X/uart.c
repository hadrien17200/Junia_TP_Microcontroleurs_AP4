#include <xc.h>
#include <stdint.h>
#include "uart.h"

void uart_init(void)
{
    RC6PPS = 0b10100;   // RC6 = TX
    RXPPS  = 0b10111;   // RC7 = RX

    ANSELC = 0;  // Configuration de tous les pins du port C en numérique
    
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
}

void uart_write(uint8_t c)
{
    while (!PIR1bits.TXIF){};
    TX1REG = c; //Envoi dans le terminal via UART la valeur de C
}
