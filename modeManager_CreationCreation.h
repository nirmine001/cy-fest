#ifndef MODEMANAGER_CREATIONCONCERT_H  
    #define MODEMANAGER_CREATIONCONCERT_H
    #include "modeManager_CreationHall.h"
    #include <time.h>

typedef struct {
    char artist[SIZE];
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
    int is_ended;
    char modification;
    char choice;
    char pit;
    int placepit;
    char hall[SIZE];
    int total_places;
    int reserved_places;
    int stateSeat[SIZE][SIZE];
}Concert;

ConcertHall readHallInfoFromFile(char* , char* );
void handleExistingHalls(Concert * );
void create_Concert(Concert *);
void print_featuresConcert(Concert * );
void modify (ConcertHall* , Concert *);
void modification(Concert * , ConcertHall *);
int is_concert_over(Concert* );
void check_satisfaction2(Concert * , char );
void printCREATION_CONCERT(Concert* );
void save_to_file2(Concert );
Concert readConcertInfoFromFile(char* , char* );

#endif
