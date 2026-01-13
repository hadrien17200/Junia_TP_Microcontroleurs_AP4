#include "configbits.h" // Fichier avec la configuration du microcontrôleur
#include <xc.h>         // Bibliothèque pour programmer les PIC

#define _XTAL_FREQ 8000000 // Définit la fréquence du microcontrôleur à 8 MHz

void wait_1ms(void);    // Déclaration de la fonction qui attend 1 milliseconde
void wait_125ms(void);  // Déclaration de la fonction qui attend 125 millisecondes

void config_timer2(void){
    PR2 = 32;                      // Valeur maximale du compteur Timer2 (pour le timing)
    T2CONbits.T2CKPS = 0b01;       // Prescaler = 1:4 (divise la vitesse par 4)
    T2CONbits.T2OUTPS = 0b1111;    // Postscaler = 1:16 (divise encore par 16)
    T2CONbits.TMR2ON = 1;          // Active le Timer2 (démarre le chronomètre)
}

void wait_125ms(void){
    for(int i=0; i<125; i++){      // Répète 125 fois la boucle
        wait_1ms();                 // Attend 1ms à chaque tour = 125ms au total
    }
}

void wait_1ms(void)
{
    while(!PIR1bits.TMR2IF){}      // Attend que le Timer2 finisse son cycle (1ms)
    PIR1bits.TMR2IF = 0;           // Remet le drapeau à zéro pour le prochain cycle
}

void main(void) {
     
    TRISB = 0x00;   // Configure tous les pins du PORTB en sortie 
    TRISD = 0x00;   // Configure tous les pins du PORTD en sortie
    config_timer2(); // Initialise le Timer2 pour les délais
    
    while(1){       // Boucle infinie (le programme tourne en continu)
        
        // Allume LED B0 pendant 125ms puis l'éteint
        LATBbits.LATB0 = 1;        // Allume LED sur pin B0
        wait_125ms();               // Attend 125ms
        LATBbits.LATB0 = 0;        // Éteint LED sur pin B0
        
        // Allume LED B1 pendant 125ms puis l'éteint
        LATBbits.LATB1 = 1;        // Allume LED sur pin B1
        wait_125ms();               // Attend 125ms
        LATBbits.LATB1 = 0;        // Éteint LED sur pin B1
        
        // Allume LED B2 pendant 125ms puis l'éteint
        LATBbits.LATB2 = 1;        // Allume LED sur pin B2
        wait_125ms();               // Attend 125ms
        LATBbits.LATB2 = 0;        // Éteint LED sur pin B2
        
        // Allume LED B3 pendant 125ms puis l'éteint
        LATBbits.LATB3 = 1;        // Allume LED sur pin B3
        wait_125ms();               // Attend 125ms
        LATBbits.LATB3 = 0;        // Éteint LED sur pin B3
        
        // Allume LED D0 pendant 125ms puis l'éteint
        LATDbits.LATD0 = 1;        // Allume LED sur pin D0
        wait_125ms();               // Attend 125ms
        LATDbits.LATD0 = 0;        // Éteint LED sur pin D0
        
        // Allume LED D1 pendant 125ms puis l'éteint
        LATDbits.LATD1 = 1;        // Allume LED sur pin D1
        wait_125ms();               // Attend 125ms
        LATDbits.LATD1 = 0;        // Éteint LED sur pin D1
        
        // Allume LED D2 pendant 125ms puis l'éteint
        LATDbits.LATD2 = 1;        // Allume LED sur pin D2
        wait_125ms();               // Attend 125ms
        LATDbits.LATD2 = 0;        // Éteint LED sur pin D2
        
        // Allume LED D3 pendant 125ms puis l'éteint
        LATDbits.LATD3 = 1;        // Allume LED sur pin D3
        wait_125ms();               // Attend 125ms
        LATDbits.LATD3 = 0;        // Éteint LED sur pin D3
        
        // Le cycle recommence depuis le début (retour à LED B0)
    }
}