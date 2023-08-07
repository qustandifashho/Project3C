#ifndef CHAMPION_H
#define CHAMPION_H

typedef enum {
    MAGE,
    FIGHTER,
    SUPPORT, 
    TANK
    
} ChampionRole;




typedef struct Champion {
    ChampionRole role;
    int level;
    struct Champion* next; // used for linked list - see modules 10 slides 
} Champion;


int getRandomNumber(int min, int max);
Champion* createChampion();
Champion* addChampion( Champion *head, Champion *c );
Champion* buildChampionList( int n );
void printChampionList( Champion *head );
Champion* removeChampion( Champion *head );
Champion* destroyChampionList( Champion *head);



#endif