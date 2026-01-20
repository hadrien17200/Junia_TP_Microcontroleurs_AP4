#include "configbits.h"      // Bits de configuration du microcontroleur
#include <xc.h>              // Déclarations des registres et peripheriques du PIC
#include <stdint.h>          // Types entiers standard (uint8_t, uint16_t?)

#define _XTAL_FREQ 8000000   // Fréquence de l?oscillateur : 8 MHz


// Configuration du Timer2

void config_timer2(void) {
    PR2 = 249;                          // Valeur de periode du Timer2
                                        // Détermine la fréquence du PWM

    T2CONbits.T2CKPS = 0b10;            // Prescaler 1:16
                                        // Le timer compte 16 fois plus lentement

    T2CONbits.T2OUTPS = 0b0000;         // Postscaler 1:1
                                        // Pas de division supplementaire

    T2CONbits.TMR2ON = 1;               // Activation du Timer2
}

 //Configuration du PWM4 qui permet de contrôler l?intensité de la LED D1

void config_pwm4(void) {
    PWM4DCH = 25;                       // 8 bits de poids fort du rapport cyclique
    PWM4DCL = 0;                        // 2 bits de poids faible du rapport cyclique

    PWM4CONbits.PWM4EN = 1;             // Activation du module PWM4
    PWM4CONbits.PWM4POL = 0;            // Polarite normale :
                                        // sortie à 1 quand le PWM est actif
}


// Connexion du PWM4 à la broche RD0 grace a l'utilisation du systeme PPS (Peripheral Pin Select)

void config_pps(void) {
    TRISDbits.TRISD0 = 0;               // RD0 configuree en sortie
    RD0PPS = 0x0F;                      // Association du signal PWM4 à RD0
}


// Configuration des broches en entree et sortie

void config_pins(void) {

    // ----- LED D1 sur RD0 -----
    TRISDbits.TRISD0 = 0;               // RD0 en sortie
    PORTDbits.RD0 = 0;                  // LED eteinte au demarrage

    // ----- Bouton S1 sur RB0 -----
    TRISBbits.TRISB0 = 1;               // RB0 configuree en entree
    ANSELBbits.ANSB0 = 0;               // RB0 en mode numérique
}


// Modification du rapport cyclique du PWM

void set_rapport_cyclique(uint8_t pourcentage) {

    uint16_t valeur_10bits;             // Variable pour le calcul sur 10 bits

    // Securite : limiter le pourcentage à 100 %
    if (pourcentage > 100) {
        pourcentage = 100;
    }

    // Conversion du pourcentage en valeur PWM (0 à 1000 environ)
    valeur_10bits = pourcentage * 10;

    // Répartition de la valeur PWM sur les registres
    PWM4DCH = (uint8_t)(valeur_10bits >> 2);          // 8 bits de poids fort
    PWM4DCL = (uint8_t)((valeur_10bits & 0x03) << 6); // 2 bits de poids faible
}

void main(void) {

    // ----- INITIALISATION -----
    config_pins();          // Configuration des entrees/sorties
    config_timer2();        // Initialisation du Timer2
    config_pwm4();          // Initialisation du PWM4
    config_pps();           // Liaison PWM4 ? RD0

    // ----- BOUCLE INFINIE -----
    while(1) {

        // Test de l?état du bouton S1
        if (PORTBbits.RB0 == 1) {
            // Bouton relache
            set_rapport_cyclique(10);   // LED allumee à 10 %
        }
        else {
            // Bouton appuye
            set_rapport_cyclique(100);  // LED allumee à 100 %
        }
    }
}
