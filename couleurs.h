#ifndef COULEURS
#define COULEURS
#include <stdio.h>

// Efface l'écran et replace le curseur en haut à gauche
#define clrscr() printf("\033[H\033[2J")

// Sélection de couleurs
#define couleur(code) printf("\033[%sm", code)

#endif 














/*for (int i = 0; i < h->num_rows; i++) {
    printf("- R%d\n", i + 1);
} */

