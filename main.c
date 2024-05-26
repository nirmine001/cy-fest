#include "modefestivalier.h"
#include "couleurs.h" 


int main (){
    char mode = 0; //initialisée à 0. Elle servira à stocker le choix de l'utilisateur.
    ConcertHall *hall = NULL;
    int nbrh;
    Concert *h = NULL;

    while (1){ //boucle qui tourne indéfiniment. L'expression 1 est toujours vraie
        do{
        printf("choose the mode : (1 for MANAGER, 2 for FESTIVAL-GOER, 3 to Exit): ");
        scanf (" %c", &mode); 
        }while (mode != '1' && mode != '2' && mode !='3');
        
        if (mode == '3'){
            break; //quitter programme
        }	
        else if (mode == '1'){
            printf("\nYou are in MANAGER mode.\n");
            printf("\nHow many concert halls do you want to create for the festival?: ");
            scanf("%d",&nbrh);
            hall = malloc(nbrh * sizeof(ConcertHall));
            if (hall == NULL) {
                printf("Memory allocation problem! \n");
                exit(1);
            }
             for (int i = 0; i< nbrh; i++) {
                printCREATION_HALL(&hall[i]);
            }
            printf("\nHow many concert do you want to create for the festival?: ");
            scanf("%d",&nbrh);
            h = malloc(nbrh * sizeof(Concert));
            if (h == NULL) {
                printf("Memory allocation problem! \n");
                exit(1);
            }
            for (int i = 0; i< nbrh; i++) {
                printCREATION_CONCERT(&h[i]);
            }
            
        }
        else if (mode == '2'){ 
            void printfMODEFESTIVALIER(nbrh);
        } 

        else{
        printf("Error in your choice. Please choose again.\n");
        mode=0;
    }
    }
    
    if (hall) {
        for (int i = 0; i < nbrh; i++) {
            free(hall[i].seats_per_row); // En laissant la libération de la mémoire à l'appelant, cela clarifie les responsabilités
        }
        free(hall);
    }
    if(h){
        free(h);
    }

 return 0;
}

