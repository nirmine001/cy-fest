#include "modeManager_CreationConcert.h"


void create_Hall(ConcertHall *h) { //pointer allows the function to directly modify the original structure
    int seat;
    printf("\nYou will start to give the features of the hall independently of the categories: \n");
    
    printf("\nEnter the name: ");
    scanf("%s", h->name);

    do{
    printf ("\nEnter the total number of rows: ");
    scanf ("%d",&h->num_rows);
    }while (h->num_rows < 1);

    do{
    printf("\nYou have 2 choices for the setup of the seats: \n Press 1: You want all rows to have the same number of seats.\n Press 2: You want a different number of seats for each row.\n");
    scanf(" %c", &h->choice);
    if(h->choice == '1'){
        printf("Enter a number of seats for all rows: \n");
        scanf("%d",&seat);
        h->seats_per_row = (int *)malloc(h->num_rows * sizeof(int)); //In C, malloc returns a void * pointer (generic pointer), and needs to be converted to the appropriate pointer type, in this case a pointer to an integer (int *).
        if (h->seats_per_row == NULL) {                           
            printf("Memorry allocation problem !\n");
            exit(1);
        }
        for (int i = 0; i < h->num_rows; i++) {  //for all rows
            h->seats_per_row[i] = seat; //seats will all be equal to seats, i.e. the same number
        } 
    }

    else if (h->choice=='2'){
        h->seats_per_row = (int *)malloc( h->num_rows* sizeof(int)); //chatgpt
        if(h->seats_per_row == NULL){ 
            printf("Memory allocation problem! \n ");
            exit (1);
        }
        printf("How many seats are there in: \n");
        for (int i=0; i<h->num_rows; i++){
            printf("row %d ?\n", i+1);
            scanf("%d", &h->seats_per_row[i]); ////nbr of seats in row i &h->seats[i]
        }
    }
    else {
        printf("Error in your choice. Please choose beetween 1 and 2.\n");
        printf("\n");
    } 
    }while (h->choice !='1' && h->choice !='2');
}
void print_featuresHall(ConcertHall* h) {
    printf("\n name: %s, number of rows in the hall: %d\n",h->name, h->num_rows);
    if (h->choice=='1'){
        printf(" number of seats for all rows: %d\n",h->seats_per_row[0]);
    }
    else {
        printf(" Number of seats in row:\n");
        for (int i = 0; i < h->num_rows; i++) {
            printf("- R%d: %d seats\n", i + 1, h->seats_per_row[i]);
        }
    }
}

void create_CatA(ConcertHall* a) { 
    int i;
    printf("\nEnter the features of the categorie A:\n");
    printf("\n");
    do{
    printf (" Enter the number of rows in this cat: ");
    scanf ("%d", &a->A_rows);
    }while (a->A_rows < 0 || a->A_rows > a->num_rows);

    do{
    printf (" Enter the price: ");
    scanf("%f",&a->prices[0]);
    }while(a->prices[0] < 1);

    if (a->choice=='1'){
        a->seats_in_catA = a->A_rows * a->seats_per_row[0]; // a->seats_per_row[O] : it's the number of seats in row 1 because it's always the same.
    }
    else {
        int r=0;
        for (i=0; i<a->A_rows; i++) { //from row 1 to the last row of cat A
              r = r+a->seats_per_row[i]; // We're adding seats
        } 
          a->seats_in_catA = r;
    }
}
void print_CatA(ConcertHall* a) {
    printf("\n number of rows: %d, price: %g$, the number of seats will be: %d. \n", a->A_rows, a->prices[0], a->seats_in_catA);//%g eliminates unnecessary 0   
}

void create_CatB(ConcertHall* b) {
    printf("\nEnter the features of the categorie B:\n");
    int i; 
    printf("\n");
    do{
    printf (" Enter the number of rows in this cat: ");
    scanf ("%d", &b->B_rows);
    }while (b->B_rows < 0 || b->B_rows + b->A_rows > b->num_rows);

    do{
    printf (" Enter the price: ");
    scanf("%f",&b->prices[1]);
    }while(b->prices[1] < 1);

    if (b->choice=='1'){
        b->seats_in_catB = b->B_rows * b->seats_per_row[0]; 
    }
    else {
        int r=0;
        for (i=b->A_rows; i < b->A_rows + b->B_rows; i++) { //from the last row in category A to the last row in category B, i.e. as long as i is less than the total number of rows in category B plus the last row in category A.
            r +=b->seats_per_row[i]; 
        }
        b->seats_in_catB = r;
    }
}
void print_CatB(ConcertHall * b) {
    printf("\n number of rows: %d, price: %g$, the number of seats will be: %d.\n", b->B_rows, b->prices[1], b->seats_in_catB);
}

void create_CatC(ConcertHall* c) {
    printf("\nEnter the features of the categorie C:\n");
    int i;

    int s=c->A_rows+c->B_rows;
    int r = c->num_rows;
    if (s < r){
        c->C_rows = r-s;
    }

    do{
    printf (" Enter the price: ");
    scanf("%f",&c->prices[2]);
    }while(c->prices[2] < 1);

    if (c->choice=='1'){
        c->seats_in_catC = c->C_rows * c->seats_per_row[0]; //number of row in catC x nbr of seats per row
    }
    else {
        int r=0;
        for (i=c->A_rows + c->B_rows; i < s + c->C_rows; i++) { //from the last range of cat B+1 to the last of cat C
            r += c->seats_per_row[i]; 
        }
        c->seats_in_catC = r;
    }
}
void print_CatC(ConcertHall * c) {
    printf("\n number of rows: %d, price: %g$, the number of seats will be: %d.\n", c->C_rows, c->prices[2], c->seats_in_catC);
}

void check_satisfaction1(ConcertHall *hall, char creation){
    int satisfied = 0; //we assume he's not satisfied
        while (!satisfied) { //as long as satisfied is not true either = 1

            switch(creation){
                case 'r' : 
                    create_Hall(hall);
                    printf("\nWould you like to change your choices? :\n");
                    print_featuresHall(hall);
                break;    
                case 'A' : 
                    create_CatA(hall);
                    printf("\nWould you like to change your choices? :\n");
                    print_CatA(hall);
                break; 
                case 'B' :
                    create_CatB(hall);
                    printf("\nWould you like to change your choices? :\n");
                    print_CatB(hall);
                break; 
                case 'C' : 
                    create_CatC(hall);
                    printf("\nWould you like to change your choices? :\n" );
                    print_CatC(hall);
                break; 
            }
            char response;
            printf("\n");
            do{
            printf("Enter 'y' for yes or 'n' for no: ");
            scanf(" %c", &response);//space doesn't display \n so phrases 2 times
            }while(response !='y' && response !='Y' && response !='n' && response !='N' );

            if (response == 'y' || response == 'Y') {
                printf("Let's try again!\n"); 
                satisfied = 0;} 
            else if (response == 'n' || response == 'N') {
                satisfied = 1;}
        }
} 

void save_to_file1(ConcertHall hall) {
    FILE *file = fopen("hallinfo.txt", "a+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "Name of the hall: %s\n", hall.name);
    fprintf(file, "Number of rows: %d\n", hall.num_rows);
    fprintf(file, "Choice of configuration : %c\n", hall.choice);
    if (hall.choice=='1'){
    fprintf(file, "Number of seats per row: %d\n", hall.seats_per_row[0]);
    }
    else {
        for (int i = 0; i < hall.num_rows; i++) {
            fprintf(file,"- R%d: %d seats\n", i + 1, hall.seats_per_row[i]);
        }
    }
    fprintf(file, "Number of rows in each category (A,B,C): %d, %d, %d\n", hall.A_rows, hall.B_rows, hall.C_rows);
    fprintf(file, "Number of seats in each category (A,B,C): %d, %d, %d\n", hall.seats_in_catA, hall.seats_in_catB, hall.seats_in_catC);
    fprintf(file, "Ticket prices for each category (A,B,C): %g$, %g$, %g$\n", hall.prices[0], hall.prices[1], hall.prices[2]);

    fclose(file);
}

void printCREATION_HALL(ConcertHall* hall){
    check_satisfaction1(hall,'r');//pass as argument the address so we modify hall
    check_satisfaction1(hall,'A');
    check_satisfaction1(hall,'B');
    check_satisfaction1(hall,'C');
    save_to_file1(*hall);
}
