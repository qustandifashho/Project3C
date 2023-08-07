#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "champion.h"

#define TRUE 1
#define FALSE 0

int main( int argc, char *argv[] )
{

    // Seed random number generator
    srand(time(NULL));

    if (argc != 2) { // not sure what number 
        printf("Error: Invalid command line arguments Missing number of champions for each player.\n");
        return 1;
    }

    int numberOfChampions = atoi(argv[1]); //  game requires the number of champions to be an integer value to determine the size of the linked list for each player. so use atoi from string to int of cmd line arg.

    if (numberOfChampions <= 0) {
        printf("Error: Invalid number of champions. Please provide a positive integer.\n");
        return 1;
    }

    printf("============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n");
 
    // build champion linked list based on size passed through cmd line. 
    // number of champions you start with is what is passed through the command line,

    // two players playing 
    int numberOfPlayers = 2; 
    printf("The NUMBER of players is: %d\n", numberOfPlayers);

    Champion* player1 = buildChampionList(numberOfChampions);
    Champion* player2 = buildChampionList(numberOfChampions);

    /*printf("\nPlayer 1: ");  
    printChampionList(player1);  

    printf("Player 2: ");  
    printChampionList(player2);*/ 
  
    int roundNumber = 1; // initialize round number. 
    while (numberOfChampions > 0) // numberOfChampions > 1 or 2 // true
    {
        printf("\n----- ROUND %d -----", roundNumber);


        printf("\nPlayer 1: ");  
        printChampionList(player1);  

        printf("Player 2: ");  
        printChampionList(player2);

        // Player 1 MAGE vs Player 2 MAGE (or vice versa here )
        if(player1->role == MAGE && player2->role == MAGE)
        {
            printf("Player 1 is a MAGE and player 2 is a MAGE\n");
            if(player1->level >  player2->level)
            {
                // player gains a new champ while the opposing loses one :
                printf("Player 1 wins and gains one new champion. Player 2 loses one champion.\n");
                player1 = addChampion(player1, createChampion()); // adds a new champion to the champion list of the current player (player1). Create champiosn is what ramdomizes for next time 
                player2 = removeChampion(player2); //  calculates the index of the opposing player to alternate 
            }
            else if(player1->level < player2->level)
            {
                printf("Player 2 gains a new champion. Player 1 loses one champion.\n");
                player2 = addChampion(player2, createChampion());
                player1 = removeChampion(player1);
            }
            else // When there is a tie, each player loses a champ (Info from TA)
            {
                player1 = removeChampion(player1);
                player2 = removeChampion(player2);
                printf("Nothing happens\n");
            }

        }

        // Player 1 MAGE vs Player 2 FIGHTER
        else if(player1->role == MAGE && player2->role == FIGHTER){
            printf("Player 1 is a MAGE and Player 2 is a FIGHTER\n");
            if(player1->level > player2->level)
            {
                printf("Player 1 (MAGE) gains a champion");
                player1 = addChampion(player1, createChampion());
                
                
            }
            else if(player1->level < player2->level)
            { 
                printf("Player 2 (FIGHTER) loses\n");
                player2 = removeChampion(player2);

            }
            else 
            {
                player1 = removeChampion(player1);
                player1 = removeChampion(player1);
                printf("Nothing happens\n");
            }
        }

        // Player 1 MAGE vs Player 2  SUPPORT  
        else if (player1->role == MAGE && player2->role == FIGHTER)
        {
            printf("Player 1 is a MAGE and Player 2 is a SUPPORT\n");
            if(player1->level > player2->level){
                // if mage wins, they gain 1 new champion and support loses two champs
                printf("Player 1 (MAGE) gains one new champion");
                player1 = addChampion(player1, createChampion()); // add champion to mage 
                printf("Player 2 (SUPPORT) loses 2 champions");
                player2 = removeChampion(player2);
                player2 = removeChampion(player2);

                }

            

            // when SUPPORT wins, main loses 1
            else if(player1-> level < player2->level)
            { // player 1 less than 2 in leve
                printf("player 2 (SUPPORT) gains two new champions.\n");
                printf("player 1 (MAGE)  loses a champions.\n");
                player2 = addChampion(player2, createChampion()); // support gains a champ
                player2 = addChampion(player2, createChampion()); // support gains a champ again
                player1 = removeChampion(player1); // mage loses a champ 
            }

            else
            {
                player1 = removeChampion(player1);
                player2 = removeChampion(player2);
                printf("Tie nothing happens\n");
            }
        }

        // Player 1 MAGE vs Player 2 TANK
        else if(player1->role == MAGE && player2->role == TANK)
        {
            printf("Player 1 is  MAGE and Player 2 is a TANK\n");
            player1 = addChampion(player1, createChampion());
            printf("Player 1 gains a new champion.\n");
            player2 = removeChampion(player2);
            printf("layer 2 loses a champion.\n");
        }

        // Player 1 FIGHTER vs Player 2 FIGHTER 
        else if(player1->role == FIGHTER && player2->role == FIGHTER)
        {
            printf("Player 1 is a FIGHTER and Player 2 is a FIGHTER.\n");
            player1 = addChampion(player1, createChampion());
            player2 = addChampion(player2, createChampion());
            printf("Player 1 and Player 2 Gain a new Champion\n");
        }

        // Player 1 FIGHRTER vs Player 2 SUPPORT
        else if(player1->role ==FIGHTER && player2->role == SUPPORT)
        {
            printf("Player 1 is a FIGHTER and Player 2 is a SUPPORT\n");
            if (player1->level > player2->level) 
            {
                printf("Player 1 (FIGHTER) wins with no reward\n");
                printf("Player 2 (SUPPORT) Loses a champion\n");

                player2 = removeChampion(player2);
            }
            else if (player1->level < player2->level) 
            {
                printf("Player 2 (SUPPORT) wins and gains a new champion.\n");
                player2 = addChampion(player2, createChampion());
                printf("Player 1 (FIGHTER) loses but with no penalty\n");
            } 
            else 
            {
                player1 = removeChampion(player1);
                player2 = removeChampion(player2);
                printf("Tie nothing happens.\n");
            }
        }

        //Player 1 FIGHTER vs Player 2 TANK
        else if (player1->role == FIGHTER && player2->role == TANK)
        {
            printf("Player 1 is a FIGHTER and Player 2 is a TANK\n");
            printf("Player 1 (FIGHTER) wins and gains a new champion\n");
            printf("Player 2 (TANK) loses with no penlaty\n");
            player1 = addChampion(player1, createChampion());
            // no penalty fir tank 
        }

        // Player 1 SUPPORT vs Player 2 SUPPORT
        else if (player1->role == SUPPORT && player2->role == SUPPORT) 
        {
            printf("Player 1 is a SUPPORT and Player 2 is a Support\n");
            printf("Player 1 (SUPPORT) and Player 2 (SUPPORT) lose one champion.\n");
            player1 = removeChampion(player1);
            player2 = removeChampion(player2);
        }

        // Player 1 SUPPORT vs Player 2 TANK
        else if(player1->role == SUPPORT && player2->role == TANK){
            printf("Player 1 is a SUPPORT and Player 2 is a TANK\n");
            printf("Player 2 (TANK) wins and gains a new champion\n");
            printf("Player 1 (SUPPORT) loses with no penalty\n");
            player2 = addChampion(player2, createChampion());

        }

        // Player 1 TANK vs Player 2 TANK
        else if(player1->role == TANK && player2->role == TANK)
        {
            printf("Player 1 is a TANK and Player 2 is a TANK\n");
            printf("Tie nothing happens\n"); 
            player1 = removeChampion(player1);
            player2 = removeChampion(player2);
        }


        // Player 2 MAGE vs Player 1 MAGE (FM)
        else if(player2->role == MAGE && player1->role == FIGHTER)
        {
            printf("Player 2 is MAGE and Player 1 is FIGHTER\n");
            if(player2->level > player1->level){
                printf("Player 2 (MAGE) wins and gains a new champion\n");
                player2 = addChampion(player2, createChampion());
                printf("Player 1 (FIGHTER) loses with no penalty\n");

            }
            else if(player1->level > player2->level){
                printf("Player 1 (FIGHTER) wins with no reward\n");
                printf("Player 2 loses one champion\n");
                player2 = removeChampion(player2);

            }
            else{
                printf("Tie nothing happens\n");
                player1 = removeChampion(player1);
                player2 = removeChampion(player2);

            }
        

        }

        // Player 1 SUPPORT vs PLAYER 2 MAGE 
        else if(player1->role == SUPPORT && player2->role == MAGE)
        {
            printf("Player 1 is SUPPORT and Player 2 is MAGE\n");
            if(player1->level > player2->level){ // support > mage 
                // two new champs for support. mage loses one 
                printf("Player 1 (SUPPORT) wins and gains two new champions\n");
                player1 = addChampion(player1, createChampion());
                player1 = addChampion(player1, createChampion());
                printf("Player 2 (MAGE) loses one champion\n");
                player2 = removeChampion(player2);

            }
            else if(player1->level < player2->level){ // support < mage
                // one new champ for mage and support loses 2 champs 
                printf("Player 1 (SUPPORT) loses two champions\n");
                player1 = removeChampion(player1);
                player1 = removeChampion(player1);
                printf("Player 2 (MAGE) wins and gains one new champion\n");
                player2 = addChampion(player2, createChampion());
            }
            else{
                player1 = removeChampion(player1);
                player2 = removeChampion(player2);
                printf("Tie. Nothing happens\n");
            }

        }

        // Player 1 TANK vs Player 2 MAGE 
        else if(player1->role == TANK && player2->role == MAGE){
            printf("Player 1 is a TANK and Player 2 is a MAGE\n");
            printf("Player 1 (TANK) loses one champion\n");
            player1 = removeChampion(player1);
            printf("Player 2 (MAGE) wins and gains a new champion\n");
            player2 = addChampion(player2, createChampion());
        }

        // Player 1 SUPPORT vs Player 2 FIGHTER 
        else if(player1->role == SUPPORT && player2->role == FIGHTER){
            printf("Player 1 is a SUPPORT and Player 2 is a FIGHTER\n");
            if(player1->level < player2->level){ // support (1) < fighter (2) (SUPPORT LOSES, FIGHTER WINS)
                printf("Player 1 (SUPPORT) loses one champion\n");
                player1 = removeChampion(player1);
                printf("Player 2 (FIGHTER) wins but gains no champions\n");
            }
            if(player1->level > player2->level){ // support > fighter (support wins)
                printf("Player 1 (SUPPORT) wins and gains a new champion\n");
                player1 = addChampion(player1, createChampion());
                printf("Player 2 (FIGHTER) loses with no penalty\n");
            }
            else{
                player1 = removeChampion(player1);
                player2 = removeChampion(player2);
                printf("Nothing happens\n");
            }
        }


        // Player 1 TANK vs Player 2 FIGHTER
        else if(player1->role == TANK && player2->role == FIGHTER)
        {
            printf("Player 1 is a TANK and Player 2 is a FIGHTER\n");
            printf("Player 1 (TANK) loses but with no penalty\n");
            printf("Player 2 (FIGHTER) wins and gains a new champion\n");
            player2 = addChampion(player2, createChampion());
        }

        // Player 1 TANK vs PLAYER 2 SUPPORT 
        else if (player1->role == TANK && player2->role == SUPPORT)
        {
            printf("Player 1 is a TANK and Player 2 is a SUPPORT\n");
            // player 1 tank wins 
            printf("Player 1 (TANK) wins and gains a new champion\n");
            player1 = addChampion(player1, createChampion());
            printf("Player 2 (SUPPORT) loses but with no penalty\n");
        }


        printf("\n");
        roundNumber++;

        int playersWithChampions = 1; // come back to
        for (int i = 0; i < numberOfPlayers; i++) {
            if (player1 != NULL) {
                playersWithChampions++;
            }
        }

        if (playersWithChampions < 2) {
            printf("============ GAME OVER =============\n");
            for (int i = 0; i < numberOfPlayers; i++) {
                printf("\nPlayer 1 ending champion list: ");
                printChampionList(player1);
                printf("\nPlayer 2 ending champion list: ");
                printChampionList(player2);
            }

            if (playersWithChampions == 0) { /// 
                printf("\nTIE -- both players ran out of champions.\n");
            } else {
                for (int i = 0; i < numberOfPlayers; i++) {
                    if (player1 != NULL) {
                        printf("\nPlayer %d wins.\n", i + 1);
                    }
                }
            }

            for (int i = 0; i < numberOfPlayers; i++) {
                destroyChampionList(player1);
                destroyChampionList(player2); ////////////////
                //destroyChampionList(playerChampions[i+1]);
            }





        break;
        }
    }


        return 0;
        }




    
