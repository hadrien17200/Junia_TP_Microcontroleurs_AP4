#include "configbits.h" // Bits de configuration du microcontrôleur (oscillateur, watchdog, etc.)
#include <xc.h>         // Définition des registres spécifiques au microcontrôleur PIC
#include "spi.h"        // Bibliothèque pour la communication SPI
#include "lcd.h"        // Bibliothèque pour le pilotage de l'écran LCD


void main(void) {

    // Initialisation des broches utilisées par le SPI
    SPI_InitializePins();

    // Initialisation du module SPI 
    SPI_Initialize();

    // Initialisation des broches utilisées pour le LCD
    LCD_InitializePins();

    // Initialisation de l'écran LCD 
    LCD_Initialize();

    // Efface complètement l'écran LCD
    LCD_Clear();

    // Positionne le curseur en colonne 0, ligne 0 (coin supérieur gauche)
    LCD_GoTo(0,0);

    // Affiche la chaîne de caractères sur le LCD
    LCD_WriteString("Hello, World!");

    // Boucle infinie 
    while(1){
        // Aucune instruction car sinon l'écran sintille !
    }
}
