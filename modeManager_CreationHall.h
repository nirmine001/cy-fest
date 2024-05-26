#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100



typedef struct {
    char name[SIZE];
    int num_rows;
    int *seats_per_row;// Pointer to dynamically allocate the number of seats per row
    char choice;
    int A_rows;
    int B_rows;
    int C_rows;
    int seats_in_catA;
    int seats_in_catB;
    int seats_in_catC;
    float prices[3];// A, B, C
}ConcertHall;



void create_Hall(ConcertHall* );
void print_featuresHall(ConcertHall* );
void create_CatA(ConcertHall* );
void print_CatA(ConcertHall* );
void create_CatB(ConcertHall* );
void print_CatB(ConcertHall *);
void create_CatC(ConcertHall* );
void print_CatC(ConcertHall *);
void check_satisfaction1(ConcertHall * , char );
void save_to_file1(ConcertHall );
void printCREATION_HALL(ConcertHall* );
