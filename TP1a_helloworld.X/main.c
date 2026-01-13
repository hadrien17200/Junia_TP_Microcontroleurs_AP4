#include "configbits.h" // Fichier avec la configuration du microcontroleur
#include <xc.h>         // Bibliotheque pour programmer les PIC

#define _XTAL_FREQ 8000000 // Definit la frequence du microcontroleur 8 MHz

void delai_approx(void) {
    unsigned int i, j;   // Declare deux variables pour les boucles

    for(i = 0; i < 200; i++) {      // Boucle exterieure: repete 200 fois
        for(j = 0; j < 90; j++) {   // Boucle interieure: repete 90 fois
            ;  // Ne fait rien (attente pure)
        }
    }
    // Total: 200 x 90 = 18000 cycles d'attente. Delai de quelques millisecondes
}

void main(void) {
    /* Code d'initialisation */
    
    TRISB = 0x00;   // Configure tous les pins du PORTB en sortie (pour LEDs)
    TRISD = 0x00;   // Configure tous les pins du PORTD en sortie (pour LEDs)
    
    while(1){       // Boucle infinie (le programme tourne en continu)
        
        // etape 1: Allume les 4 LEDs du bas sur PORTD
        LATD = 0x0F;       // 0x0F = 0b00001111 => allume D0, D1, D2, D3
        delai_approx();    // Attend un petit moment
        
        // etape 2: Allume les 4 LEDs du haut sur PORTD
        LATD = 0xF0;       // 0xF0 = 0b11110000 => allume D4, D5, D6, D7
        delai_approx();    // Attend un petit moment
        
        // etape 3: Allume les 4 LEDs du bas sur PORTB
        LATB = 0x0F;       // 0x0F = 0b00001111 => allume B0, B1, B2, B3
        delai_approx();    // Attend un petit moment
        
        // etape 4: Allume les 4 LEDs du haut sur PORTB
        LATB = 0xF0;       // 0xF0 = 0b11110000 => allume B4, B5, B6, B7
        delai_approx();    // Attend un petit moment
        
        // Le cycle recommence depuis le debut
    }
}