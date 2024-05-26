#ifndef MODEFESTIVALGOER_H  
  #define MODEFESTIVALGOER_H
  #include "modeManager_CreationConcert.h"

typedef struct{
    char category;
    char A;
    char B;
    char C;
}Category;

void viewConcertsAvailable(const Concert [], int ); 
void book_a_spot(Concert []);
void printfMODEFESTIVALIER(int );

#endif
