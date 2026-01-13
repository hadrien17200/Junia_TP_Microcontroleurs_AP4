#include "configbits.h" // Fichier avec la configuration du microcontrôleur
#include <xc.h>         // Bibliothèque pour programmer les PIC

#define _XTAL_FREQ 8000000 // Définit la fréquence du microcontrôleur à 8 MHz

void delai_approx(void) {
    unsigned int i, j;   // Déclare deux variables pour les boucles
  
    for(i = 0; i < 200; i++) {      // Boucle extérieure: répète 200 fois
        for(j = 0; j < 90; j++) {   // Boucle intérieure: répète 90 fois
            ;  // Ne fait rien (attente pure)
        }
    }
    // Total: 200 × 90 = 18000 cycles d'attente ? délai de quelques millisecondes
}

void main(void) {
    /* Code d'initialisation */
    
    TRISB = 0x00;   // Configure tous les pins du PORTB en sortie (pour LEDs)
    TRISD = 0x00;   // Configure tous les pins du PORTD en sortie (pour LEDs)
    
    while(1){       // Boucle infinie (le programme tourne en continu)
        
        // Étape 1: Allume les 4 LEDs du bas sur PORTD
        LATD = 0x0F;       // 0x0F = 0b00001111 => allume D0, D1, D2, D3
        delai_approx();    // Attend un petit moment
        
        // Étape 2: Allume les 4 LEDs du haut sur PORTD
        LATD = 0xF0;       // 0xF0 = 0b11110000 => allume D4, D5, D6, D7
        delai_approx();    // Attend un petit moment
        
        // Étape 3: Allume les 4 LEDs du bas sur PORTB
        LATB = 0x0F;       // 0x0F = 0b00001111 => allume B0, B1, B2, B3
        delai_approx();    // Attend un petit moment
        
        // Étape 4: Allume les 4 LEDs du haut sur PORTB
        LATB = 0xF0;       // 0xF0 = 0b11110000 => allume B4, B5, B6, B7
        delai_approx();    // Attend un petit moment
        
        // Le cycle recommence depuis le début
    }
}