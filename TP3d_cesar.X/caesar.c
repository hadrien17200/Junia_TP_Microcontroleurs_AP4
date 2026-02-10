#include <stdint.h>
#include "caesar.h"

// Alphabet utilisé pour le chiffrement de César
// Indices : 0..35
static const char k_alpha[] = "0123456789abcdefghijklmnopqrstuvwxyz";

// Taille de l'alphabet en enlevant le '\0' final)
#define ALPHA_LEN (sizeof(k_alpha) - 1)


 //La fonction caesar_transform permet un chiffrement/déchiffrement de César sur un caractère
 // Le caractère c est le caractère à transformer 
 //Le caractère offset  correspond au décalage César
 //La variable decrypt correspond à l'état 0 quand il est chiffré, et correspond à !=0 quand il est déchiffrer

uint8_t caesar_transform(uint8_t c, uint8_t offset, uint8_t decrypt)
{
    // Parcours de tout l'alphabet
    for (uint8_t i = 0; i < ALPHA_LEN; i++)
    {
        // Si le caractère courant correspond à c
        if ((uint8_t)k_alpha[i] == c)
        {
            // On le déchiffre
            if (decrypt)
            {
                // On recule dans l'alphabet 
                uint8_t pos =
                    (uint8_t)((i + ALPHA_LEN - (offset % ALPHA_LEN)) % ALPHA_LEN); // Ex => i=2 ('2'), offset=5 ? (2 + 36 - 5) % 36 = 33 ? 'x'

                // Retour du caractère déchiffré
                return (uint8_t)k_alpha[pos];
            }
            else
            {
                // On chiffre la lettre, on avance dans l'alphabet
                uint8_t pos =
                    (uint8_t)((i + (offset % ALPHA_LEN)) % ALPHA_LEN); // Ex => '2' déchiffré avec offset=5 donne 'x'

                // Retour du caractère chiffré
                return (uint8_t)k_alpha[pos];
            }
        }
    }

    // Si le caractère n'appartient pas à l'alphabet initialisé plus haut, on le renvoie tel quel
    return c;
}
