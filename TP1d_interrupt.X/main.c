#include "configbits.h" // Fichier avec la configuration du microcontroleur
#include <xc.h>         // Bibliothque pour programmer les PIC
#define _XTAL_FREQ 8000000 // Definit la frequence du microcontroleur a 8 MHz

volatile int timer = 0;             // Compteur pour les interruptions du Timer2 (volatile car modifie dans l'ISR)
volatile unsigned char etape = 0;   // etape actuelle du chenillard (0 a 7)

void config_timer2(void){
    PR2 = 32;                      // Valeur maximale du compteur Timer2 (pour le timing)
    T2CONbits.T2CKPS = 0b01;       // Prescaler = 1:4 (divise la vitesse par 4)
    T2CONbits.T2OUTPS = 0b1111;    // Postscaler = 1:16 (divise encore par 16)
    T2CONbits.TMR2ON = 1;          // Active le Timer2 (dmarre le chronomtre)
}

void __interrupt() ISR (void) {
    if(PIR1bits.TMR2IF) {          // Verifie si l'interruption vient du Timer2
        PIR1bits.TMR2IF = 0;       // Remet le drapeau a zero pour le prochain cycle
        timer++;                    // Incremente le compteur

        if(timer >= 125){          // Si 125ms se sont decoules (125 interruptions 1ms)
            timer = 0;              // Reinitialise le compteur

            //teint toutes les LEDS
            PORTB = 0x00;
            PORTD = 0x00;
            
            // Allume la LED correspondant a l'etape actuelle
            switch(etape) {
                case 0: PORTB = 0b00000001; break;  // LED B0
                case 1: PORTB = 0b00000010; break;  // LED B1
                case 2: PORTB = 0b00000100; break;  // LED B2
                case 3: PORTB = 0b00001000; break;  // LED B3
                case 4: PORTD = 0b00000001; break;  // LED E0 (D0)
                case 5: PORTD = 0b00000010; break;  // LED E1 (D1)
                case 6: PORTD = 0b00000100; break;  // LED E2 (D2)
                case 7: PORTD = 0b00001000; break;  // LED E3 (D3)
            }

            etape++;                // Passe a l'etape suivante
            if(etape > 7) {         // Si on depasse la derniere LED
                etape = 0;          // Revient a la premiere LED
            }
        }
    }
}

void configure_interruptions(void){
    PIE1bits.TMR2IE = 1;          // Active l'interruption du Timer2
    INTCONbits.PEIE = 1;          // Active les interruptions peripheriques
    INTCONbits.GIE = 1;           // Active les interruptions globales
}

void main(void) {
     
    TRISB = 0x00;   // Configure tous les pins du PORTB en sortie 
    TRISD = 0x00;   // Configure tous les pins du PORTE en sortie
    PORTB = 0x00;   // Eteint toutes les LEDS du PORTB au demarrage
    PORTD = 0x00;   // Eteint toutes les LEDS du PORTE au demarrage
    
    config_timer2();             // Initialise le Timer2 pour les delais
    configure_interruptions();   // Initialise les interruptions
    
    while(1){       // Boucle infinie vide
        // Le chenillard fonctionne automatiquement grace a l'ISR !
        // Le microcontroleur attend, car l'interruption fait tout le travail
    }
}