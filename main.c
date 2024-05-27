#include "modefestivalgoer.h"
#include "couleurs.h" 


int main (){
    char mode = 0; //Set to 0. This will be used to store the user's choice.
    ConcertHall *hall = NULL;
    int nbrh;
    Concert *h = NULL;

    while (1) { //loop that rotates indefinitely. Expression 1 is always true
        do {
            printf("choose the mode : (1 for MANAGER, 2 for FESTIVAL-GOER, 3 to Exit): ");
            scanf("%c", &mode);  

            if (mode == '3') {
                break; // quitter programme
            }	
            else if (mode == '1') {
                printf("\nYou are in MANAGER mode.\n");
                printf("\nHow many concert halls do you want to create for the festival?: ");
                scanf("%d", &nbrh);
                hall = malloc(nbrh * sizeof(ConcertHall));
                if (hall == NULL) {
                    printf("Memory allocation problem! \n");
                    exit(1);
                }
                for (int i = 0; i < nbrh; i++) {
                    printCREATION_HALL(&hall[i]);
                }
                printf("\nHow many concert do you want to create for the festival?: ");
                scanf("%d", &nbrh);
                h = malloc(nbrh * sizeof(Concert));
                if (h == NULL) {
                    printf("Memory allocation problem! \n");
                    exit(1);
                }
                for (int i = 0; i < nbrh; i++) {
                    printCREATION_CONCERT(&h[i]);
                }
            }
            else if (mode =='2') {
                printf("\nYou are in FESTIVALGOER mode.\n");
                printfMODEFESTIVALGOER(nbrh); 
            } else {
                printf("Error in your choice. Please choose again.\n");
                mode = 0;
            }
        } while (mode != '1' && mode != '2' && mode != '3');
    }
    
    if (hall) {
        for (int i = 0; i < nbrh; i++) {
            free(hall[i].seats_per_row); // Leaving memory release to the caller clarifies responsibilities
        }
        free(hall);
    }
    if(h){
        free(h);
    }

 return 0;
}
