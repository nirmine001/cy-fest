#include "modefestivalgoer.h"
#include "couleurs.h"

void viewConcertsAvailable(Concert concerts[], int nbConcerts) { 
    //concerts[]: This is an array-type parameter that contains Concert-type elements(the structure).
    // this function scans all concerts and displays the name, venue, start and end times, as well as the number of seats available for each concert. It will display a list of available concerts with all the details mentioned before. 
    for (int i = 0; i < nbConcerts; i++) {
        Concert concert = readConcertInfoFromFile("concertinfo.txt", concerts[i].artist);
        printf("Concert: %s\n", concerts[i].artist);
        printf("Concert Hall : %s\n", concert.hall);
        printf("Start time: %02d:%02d\n", concerts[i].start_hour, concerts[i].start_minute);
        printf("End time: %02d:%02d\n", concerts[i].end_hour, concerts[i].end_minute);
        printf("Available places: %d\n", concerts[i].total_places - concerts[i].reserved_places);
        printf("\n");
    }
}

    //It displays available concerts, it asks the user to choose a concert to book seats, it displays the seating plan for the chosen concert, it allows the user to book a certain number of seats by entering the rank and seat number.
void book_a_spot(Concert concerts[]) {

    char concertname[SIZE];
    printf("\nPlease enter the name of the artist for the concert you wish to book:\n");
    scanf("%s", concertname);
    Concert concert;
    if (strcmp(concertname, concert.artist)!= 0){//choose a concert that exists!
        printf("Invalid name, please enter a valid name.\n");
    }  
    concert = readConcertInfoFromFile("concertinfo.txt", concertname);
    ConcertHall hall;
    hall = readHallInfoFromFile("hallinfo.txt", concert.hall);
    
    printf("\nThere are two seating plans : 1 All the seats per rows are the same, 2 Every rows have different seats per row\n");
    printf("Seating plan for the concert %c in the hall %s :\n", hall.choice, concert.hall);

    for (int i = 0; i < concerts[hall.choice].total_places; i++) { //Browse each row of seats in the selected concert.
        for (int j = 0; j < concerts[hall.choice].total_places; j++) {//Browse each seat in row i.
            if (concerts[hall.choice].stateSeat[i][j] == 0) {//=0 to say space is available.
                printf("O "); // Free place
            } else {
                printf("X "); // Reserved space
            }
        }
        printf("\n");
    } 
    
    if (concert.pit == '0'){
        printf("\nThe concert has no pit.\n");
    }
    else if(concert.pit == '1'){
        printf("\nThe concert has a pit, so you’ll be up! If you choose category A.\n");  
    }
    
    int nmbPlacetobook;
        printf("How many spots would you like to reserve?\n");
        scanf("%d ", &nmbPlacetobook);
        for (int i = 0; i < nmbPlacetobook; i++) {
            int rank, seat;
            Category * cat;
            do{
            printf("Enter the category() : \n");
            scanf("%c", &cat->category);
            }while(cat->category != 'A' || cat->category != 'B' || cat->category != 'C');
            printf("Enter the rank and the seat : \n");
            scanf("%d %d", &rank, &seat);

            if(cat->category == 'A'){
                printf("The price of a place is: %g\n", hall.prices[0]);
            }else if(cat->category == 'B'){
                printf("The price of a place is: %g\n", hall.prices[1]); 
            }else{
                printf("The price of a place is: %g\n", hall.prices[2]);
            }
        
        if (rank < 0 || rank >= concerts[hall.choice].total_places || seat < 0 || seat >= concerts[hall.choice].total_places) {//to be sure that the number of seats and rank tape exist.

            printf("Invalid rank or seat number.\n");
        } else {
            if (concerts[hall.choice].stateSeat[rank][seat] == 0){ //matrix or array has two dimensions, so if the place is free, we will reserve it and so it will be more available (so =1).
                concerts[hall.choice].stateSeat[rank][seat] = 1;// so the same place in the condition is now reserved.
                concerts[hall.choice].reserved_places++;//a new place has been booked so it is added to the places that are already booked.
                printf("Place(s) reserved successfully.\n");
                printf("Your reservation has been posted, you can see it!");
                printf("Details of your reservation: \n");
                printf("Concert: %s\n", concert.artist);
                printf("Hall: %s\n", concert.hall);
                printf("Category : %c",cat->category);
               /* printf("Place(s) reserved: %d", concert.reserved_places); */
            } else {
                printf("This place is already booked.\n");
            }
        }
    }
}
        
void printfMODEFESTIVALGOER(int nbrh){
        Concert concerts[nbrh];
        char choice;
        do {    
            do{
            printf("\nWelcome to CY'FEST! What do you want to do?\n");
            printf("1. View available concerts.\n");
            printf("2. Book one or more seats.\n");
            printf("0. Exit the program.\n");
            printf("Enter your choice: ");
            scanf(" %c", &choice); 
            switch (choice) {
                case '1':
                    viewConcertsAvailable(concerts,nbrh); // Call function to display available concerts
                    break;
                case '2':
                    book_a_spot(concerts); // Call the function to book one or more seats
                    break;
                case '0':
                    printf("Thank you for using CY'FEST. Goodbye!\n");
                break;
                default:
                    printf("Invalid. Please try again.\n");
            }
            }while(choice !='1' && choice !='2' && choice != '0');
        } while (choice != '0');
    }
