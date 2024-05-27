#include"modefestivalgoer.h"
#include "couleurs.h"  // Include header file.     

int main() {
    // Erase the screen. 
    clrscr();

    // Use the macro to define the color with multiple codes.
    couleur("47;30");
    printf("\xF0\x9F\x98\xBA""Plan of the stage : ""\xF0\x9F\x98\xBA");

;// Display the text

    for (int i = 0; i < 100; i++) {  // Ajouter des espaces. 

    }
    couleur("0");  // Resetting color to default.
    printf("\n");  // go to the next line.

    // Display 99 empty lines.
    for (int i = 0; i < 99; i++) {
        couleur("47");
        printf("\n");
    }

    // Display he legend from the 80 line.
    couleur("30");
    printf("Legend : \n");
    couleur("35"); // magenta
    printf("O - Category A () \n");
    couleur("36"); // cyan
    printf("O - Category B ()\n");
    couleur("30"); // noir
    printf("O - Category C () \n");

    //Resetting color to default. 
    couleur("0");

    // Display the left lines to reach 100 lines.
    for (int i = 0; i < 1; i++) {
        printf("\n");
    }

    return 0;
}
