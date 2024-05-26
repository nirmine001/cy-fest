#include "modeManager_CreationConcert.h"
#include "couleurs.h"
// creation of the concert hall 

ConcertHall readHallInfoFromFile(const char* filename, const char* hallName) {
    ConcertHall hall;
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char buffer[SIZE];
        // read line per line until the end of file
        while (fgets(buffer, SIZE, file) != NULL) {
            // Verify if the line contains the name of the hall
            if (sscanf(buffer, "Name of the hall: %s\n", hall.name) == 1) {
                if (strcmp(hall.name, hallName) == 0) {
                    fscanf(file, "Number of rows: %d\n", &hall.num_rows);
                    fscanf(file, "Choice of configuration : %c\n", &hall.choice);
                    if (hall.choice == '1') {
                        fscanf(file, "Number of seats per row: %d\n", &hall.seats_per_row[0]);
                    } else {
                        for (int i = 0; i < hall.num_rows; i++) {
                            fscanf(file, "- R%d: %d seats\n", &i + 1, &hall.seats_per_row[i]);
                        }
                    }
                    fscanf(file, "Number of rows in each category (A,B,C): %d, %d, %d\n", &hall.A_rows, &hall.B_rows, &hall.C_rows);
                    fscanf(file, "Number of seats in each category (A,B,C): %d, %d, %d\n", &hall.seats_in_catA, &hall.seats_in_catB, &hall.seats_in_catC);
                    fscanf(file, "Ticket prices for each category (A,B,C): %g$, %g$, %g$\n", &hall.prices[0], &hall.prices[1], &hall.prices[2]);
                    fclose(file);
                    return hall;
                }
            }
        }
        fclose(file);
    } else {
        printf("Error opening file.\n");
    }
    return hall;
}

void handleExistingHalls(Concert *c) {
    int found;
    ConcertHall a;
    do {
        FILE *file = fopen("hallinfo.txt", "r");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        printf("Here are your different halls: \n");
        char buffer[SIZE]; // Buffer to read the lines of the file
            while (fgets(buffer, SIZE, file) != NULL) {// reads and displays all the hall names of the the file. We use a loop while to read the file line by line.
                if (sscanf(buffer, "Name of the hall: %s\n", a.name) == 1) {
                        printf("%s\n", a.name);
                }   
            }

        fclose(file);
        printf("Print the name of the hall that you want to assign: \n");
        scanf("%s", c->hall);

        // Verify if the name of the hall entered by the user exists in the file.
        file = fopen("hallinfo.txt", "r"); // We re-open the file. 
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        found = 0;
        while (fgets(buffer, SIZE, file) != NULL) {
            if (sscanf(buffer, "Name of the hall: %s", a.name) == 1) {
    // Compare the name of the hall entered by the user (c->hall) with the name of the hall read int he file. 
                if (strcmp(c->hall, a.name) == 0) {
                found = 1;
                break;}
            }   
        }
        fclose(file);

        if (found == 1) {
            return;
        } else {
            printf("Hall not found. Please try again.\n");
        } 
    } while (found == 0);
}
    
void create_Concert(Concert *c){
    printf("You will start to give the features of the concert: \n");

    printf("\nEnter the the name of the artist performing : (please use - instead of space)\n");
    scanf("%s", c->artist);

    do {
        printf("\nAt what time does the concert start? (hours and minutes, 24-hour format):\n");
        printf("Hour: ");
        scanf("%d", &c->start_hour);
        printf("Minute: ");
        scanf("%d", &c->start_minute);
    } while (c->start_hour < 0 || c->start_hour >= 24 || c->start_minute < 0 || c->start_minute >= 60);

    do {
        printf("\nWhen does the concert end? (hours and minutes, 24-hour format):\n");
        printf("Hour: ");
        scanf("%d", &c->end_hour);
        printf("Minute: ");
        scanf("%d", &c->end_minute);
    } while (c->end_hour < c->start_hour || c->end_hour >= 24 || c->end_minute < 0 || c->end_minute>= 60);

    do {
    printf("\nFor this concert: \nWould you like to create a new hall? (press 1)\n or \nWould you like to assign an existing hall? (press 2)\n");
    scanf(" %c",&c->choice);
    if(c->choice=='1'){
        ConcertHall *b = (ConcertHall *)malloc(sizeof(ConcertHall));
        if (b == NULL) {
            printf("Memory allocation problem! \n");
            exit(1);
        free(b);
        }
        printCREATION_HALL(b);
        strcpy(c->hall, b->name);
        free(b);
    }
    else if (c->choice=='2'){
        handleExistingHalls(c);
    }
    else {
        printf("Error in your choice. Please choose beetween 1 and 2.\n");
        printf("\n");
    }
    }while (c->choice !='1' && c->choice !='2');
     printf("Salle assignée au concert : %s\n", c->hall);

    do {
    printf("\nDoes it has a pit ? (0 for no, 1 for yes) : \n");
    scanf(" %c", &c->pit);
    }while (c->pit != '0' && c->pit != '1');
    
}
void print_featuresConcert(Concert *c){
    printf("\nArtist: %s, Starting time: (%d:%d), Ending time: (%d:%d), Hall %s assigned to this concert.\n", c->artist,c->start_hour, c->start_minute, c->end_hour, c->end_minute, c->hall);
    if(c->pit=='0'){
        printf(" No pit during the concert.\n");
    }
    else {
        ConcertHall hall;
        hall = readHallInfoFromFile("hallinfo.txt", c->hall);
        // The location of a seat can contain the space of 2 festival goer.
        int r = hall.seats_in_catA;
        r= r*2;
        c->placepit = r;
        printf("Nombre de sieges dans A : %d\n", hall.seats_in_catA);
        printf(" Your concert includes a pit. Therefore, there is no cat A, but the price is the same\n");
        printf (" It will have %d places in the pit.\n",c->placepit); 
    }
}

void modify (ConcertHall* m, Concert *c){
    ConcertHall h;
    h = readHallInfoFromFile("hallinfo.txt", c->hall);
    
    printf("Old prices for each category (A,B,C): %g$, %g$, %g$\n", h.prices[0], h.prices[1], h.prices[2]);
    printf("\nGive the new price...\n");
    do{
        printf("... for cat A: ");
        scanf("%f",&m->prices[0]);
    }while (m->prices[0] < 1);
    do{
        printf("... for cat B: ");
        scanf("%f",&m->prices[1]);
    }while (m->prices[1] < 1);
    do{
        printf("... for cat C: ");
        scanf("%f",&m->prices[2]);
    }while (m->prices[2] < 1);

     printf("Number of rows: %d\n",h.num_rows);
     printf("Old number of rows in each category (A,B,C): %d, %d, %d\n",h.A_rows,h.B_rows, h.C_rows);
    printf("\nGive the new numbers of rows...\n");
    do{
       printf ("... for cat A: ");
       scanf ("%d", &m->A_rows);
    }while (m->A_rows < 0 || m->A_rows > h.num_rows);
   do{
      printf ("... for cat B: ");
      scanf ("%d", &m->B_rows);
   }while (m->B_rows < 0 || m->B_rows > h.num_rows);
    do {
        printf("\nDoes it has a pit ? (0 for no, 1 for yes) : \n");
        scanf(" %c", &c->pit);
    }while (c->pit != '0' && c->pit != '1');

    int s=m->A_rows+m->B_rows;
    int r = h.num_rows;
    if (s < r){
        m->C_rows = r-s;
    }
   if (h.choice=='1'){
       m->seats_in_catA = m->A_rows * m->seats_per_row[0];
       m->seats_in_catB = m->B_rows * m->seats_per_row[0];
       m->seats_in_catC = m->C_rows * m->seats_per_row[0];
   }
   else {
       int i;
       int r=0;
       for (i=0; i<m->A_rows; i++) { 
              r = r+m->seats_per_row[i] ; 
          } 
          m->seats_in_catA = r;
       for (i=m->A_rows; i < m->A_rows + m->B_rows; i++) {
           r +=m->seats_per_row[i];
       }
            m->seats_in_catB = r;
       for (i=m->A_rows + m->B_rows; i < s + m->C_rows; i++) { 
              r += m->seats_per_row[i]; 
          }
          m->seats_in_catC = r;
   }
    
    printf("\nNew price for cat: \n A : %g; \n B : %g; \n C : %g\n",m->prices[0], m->prices[1], m->prices[2]);
 printf("New number of rows in cat:\n A : %d;\n B : %d;\n C : %d\n",m->A_rows, m->B_rows, m->C_rows);
    printf("Number of seats in each category:\n A : %d;\n B : %d;\n C : %d\n",m->seats_in_catA, m->seats_in_catB, m->seats_in_catC);
}

void modification(Concert * c, ConcertHall * m){
    printf ("\nBecause the concert is over, you can modify the configuration of the hall.\n");
    couleur("31");
    printf("\nYou can NOT modify the name, the total number of rows, the fact that their is a pit, neither your choice of the configuartion of the seats per rows.\n");
    couleur("31");
    printf("\nIf you choose to modify, you will be asked to change everything. For example, if you wish to keep the same prices for category A, simply enter its initial price.\n");
    couleur("31");
    printf("\nYou will have only one try,please think before enterring the new informations.\n ");
    couleur("0");
    do{
    printf("\nWould you like to modify it? (0 for no, 1 for yes)\n");
    scanf(" %c", &c->modification);
    if (c->modification == '1'){
        modify(m,c);
        ConcertHall hall;
        save_to_file1(hall);
    } else if (c->modification == '0'){ 
        printf("No modification.\n");
    } else {
        printf("Error. Please choose beetween 1 and 0.\n");
    }
}while(c->modification != '1' && c->modification != '0');
} 
int is_concert_over(Concert* e) {
    time_t current_time;
    struct tm *local_time;
    // Obtain the current hour.
    time(&current_time);
    local_time = localtime(&current_time);

    int current_hour = local_time->tm_hour;
    int current_minute = local_time->tm_min;

    if (current_hour > e->end_hour || (current_hour == e->end_hour && current_minute >= e->end_minute)) {
        e->is_ended = 1;
        printf("\nthe concert is ended.\n");
       ConcertHall *h;
        modification(e,h);
    } else {
        e->is_ended = 0;
        printf("\nthe concert is not ended.\n");
    }
    return e->is_ended;
}

void check_satisfaction2(Concert *c, char creation){

    int satisfied = 0; // Imagine the user isn't satisfied.
        while (!satisfied) { // as long as satisfied is not true = 1.

            switch(creation){
                case 'r' : 
                    create_Concert(c);
                    printf("\nWould you like to change your choice? :\n");
                    print_featuresConcert(c);
                break;    
            }

            char response;
            printf("\n");
            do{
            printf("Enter 'y' for yes or 'n' for no: ");
            scanf(" %c", &response);//space allows to not display \n, so the sentence 2 times.
            }while(response !='y' && response !='Y' && response !='n' && response !='N' );

            if (response == 'y' || response == 'Y') {
                printf("Let's try again!\n"); 
                satisfied = 0;} 
            else if (response == 'n' || response == 'N') {
                satisfied = 1;}
        }
} 

void save_to_file2(Concert concert) {

    FILE *file = fopen("concertinfo.txt", "a+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Name of the artist: %s\n", concert.artist);
    fprintf(file, "Starting time: (%d:%d)\n", concert.start_hour,concert.start_minute);
    fprintf(file, "Ending time: (%d:%d)\n", concert.end_hour,concert.end_minute);
    fprintf(file, "Has the concert ended?(1 yes,0 no): %d\n", concert.is_ended);
    fprintf(file, "Contain a pit? (1 yes, 0 no): %c\n", concert.pit);
    fprintf(file, "Hall for the concert: %s\n", concert.hall);
    if (concert.is_ended==1){
        fprintf(file,"Has the concert hall been modified?(1 yes,0 no): %c\n",concert.modification);
    }
    if (concert.pit==1){
        fprintf(file, "Places in the pit: %d\n",concert.placepit);
    }
    fclose(file);
}

void printCREATION_CONCERT(Concert* c){
    check_satisfaction2(c,'r');
    is_concert_over(c);
    save_to_file2(*c);
}

Concert readConcertInfoFromFile(const char* filename, const char* artistname) {
    Concert concert;
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char buffer[SIZE];
        // Read line by line until the end of file.
        while (fgets(buffer, SIZE, file) != NULL) {
            // Verify if the line contains the name of the hall.
            if (sscanf(buffer, "Name of the artist: %s\n", concert.artist) == 1) {
                if (strcmp(concert.artist, artistname) == 0) {
                    fscanf(file, "Starting time: (%d:%d)\n", &concert.start_hour,&concert.start_minute);
                    fscanf(file, "Ending time: (%d:%d)\n", &concert.end_hour,&concert.end_minute);
                    fscanf(file, "Has the concert ended?(1 yes,0 no): %d\n", &concert.is_ended);
                    fscanf(file, "Contain a pit? (1 yes, 0 no): %c\n", &concert.pit);
                    fscanf(file, "Hall for the concert: %s\n", concert.hall);
                    if (concert.is_ended==1){
                        fscanf(file,"Has the concert hall been modified?(1 yes,0 no): %c\n",&concert.modification);
                    }
                    if (concert.pit==1){
                        fscanf(file, "Places in the pit: %d\n",&concert.placepit);
                    }
                    fclose(file);
                    return concert;
                }
            }
        }
        fclose(file);
    } else {
        printf("Error opening file.\n");
    }
    return concert;
}