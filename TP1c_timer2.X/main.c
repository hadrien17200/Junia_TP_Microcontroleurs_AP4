#include "configbits.h" // Bits de configuration
#include <xc.h>        
#define _XTAL_FREQ 8000000
void delai_approx(void) {
    unsigned int i, j;
  
    for(i = 0; i < 200; i++) {
        for(j = 0; j < 90; j++) {
            
            ; 
        }
    }
}


void main(void) {
    /* Code d'initialisation */
        
   
    TRISB = 0x00;   // PORTB en sortie
    TRISD = 0x00;   // PORTD en sortie
    
    while(1){
        /* Code a executer dans une boucle infinie */
        
        LATBbits.LATB0 = 1;
        delai_approx(); 
        LATBbits.LATB0 = 0;
        LATBbits.LATB1 = 1;
        delai_approx(); 
        LATBbits.LATB1 = 0;
        LATBbits.LATB2 = 1;
        delai_approx();
         LATBbits.LATB2 = 0; 
        LATBbits.LATB3 = 1;
        delai_approx(); 
        LATBbits.LATB3 = 0;
        LATDbits.LATD0 = 1;
        delai_approx();
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
        delai_approx();
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 1;
        delai_approx();
        LATDbits.LATD2 = 0;
        LATDbits.LATD3 = 1;
        delai_approx();
        LATDbits.LATD3 = 0;
        
    }
}
