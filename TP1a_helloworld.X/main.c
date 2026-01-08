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
        
        LATD = 0x0F;       
        delai_approx();     
        
        
        LATD = 0xF0;
        delai_approx();     
        
        LATB = 0x0F;   
        delai_approx();
        
        LATB = 0xF0;
         delai_approx();
    }
}
