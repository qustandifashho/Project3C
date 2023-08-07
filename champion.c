#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "champion.h"

int getRandomNumber(int min, int max) 
{ 
    int randomNumber = rand() % (max - min + 1) + min;
    return randomNumber;
}

Champion* createChampion(){
    // create a champion
    // randomly assign role and level based on probabilities 
    // return the created champion 

    // Dynamically allocate a new champion struct object and return a pointer to 
    // that struct object whihc will later be used to insert a linked list 
    Champion* newChamp = (Champion*)malloc(sizeof(Champion));
    if (newChamp == NULL) {
        printf("Memory allocation failed for newChamp\n"); 
        return 0;
    }

    // 1 to 100 is for the 25% chance
    int randomNum;
    randomNum = getRandomNumber(0,100); // inclusive 1 to 100 rand number then dividing into fourths 

    if(randomNum <= 25){  // 1 to 25
        newChamp -> role = MAGE;
        newChamp -> level = getRandomNumber(5,8);
        //rand() % 4 + 5; // 5 to 8
    }
    else if(randomNum <= 50){ // 26 to 50 
        newChamp -> role = FIGHTER;
        newChamp -> level = getRandomNumber(1,4);
         rand() % 4 + 1; // 1 to 4
    }
    else if(randomNum <= 75){ // 26 to 75
        newChamp -> role = SUPPORT;
        newChamp -> level = getRandomNumber(3,6);
        //rand() % 4 + 3; // 3 to 6
    }
    else{ // rest (76 to 100)
        newChamp -> role = TANK;
        newChamp -> level = getRandomNumber(1,8);
        //rand() % 8 + 1; // 1 to 8
    }

    newChamp->next = NULL;
    

    return newChamp; // Return the new champion

}

Champion* addChampion( Champion *head, Champion *c ){
  
    
    // head of linked list - head (first node of linked list)
    // c  - new champion (newChamp in prev fxn)
    // new Champion struct object to the linked list that head is pointing at. 

    // If the linked list is empty or the new champion's level is greater than the head's level,
    // insert the new champion as the new head of the list
    if(head == NULL || c->level > head->level){
        c->next = head;
        return c;

    }
    Champion* currChampion = head;
    // insert new champ after traversing linked list
    // initialize a pointer current to point to the head of the linked list.

    // loop to find the right place to insert the new champ.  
    while(currChampion->next != NULL){
    // && currChampion->next->level >= c->level && currChampion->next->role > c->role){ // NULL is end of linked list, traverse til end 
        // checks if the level of the next champion (current->next->level) is greater than or equal to the level of the new champion (c->level)
        currChampion = currChampion->next; // if currChampion >= level of newchamp move to the next node in list 
    }
    // Insert the new champion after the current position
    c->next = currChampion->next; // sets 'next' pointer of new champ c to point to the node tha comes after currChamp node
    currChampion->next = c; // updates 'next' pointer of the 'currChampion; node to point to the new champ 'c' (inserts newChamp 'c' into linked list after currChamp node)
    
    return head; // (head of linked list)


}











Champion* buildChampionList( int n ){

    // build a list of champions using linked list. 
    Champion* head = NULL; // Initialize head (first node) to Null

    // create n champions and add them to the linked list:
    for(int i = 0; i < n; i++){
        Champion* newChamp = createChampion(); // functions call to create a new champion
        head = addChampion(head, newChamp);
        //printf("%p", head);
    }
    return head; // return head of new linked list 

}

void printChampionList( Champion *head ){
    if(head == NULL){
        printf("Empty Linked List \n"); // checking 
        return;
    }
    Champion* current = head;
    while(current != NULL) {
        char roleType;
        if (current -> role == MAGE) {
            roleType = 'M';
        }
        else if(current -> role == FIGHTER){
            roleType = 'F';
        }
        else if(current -> role == SUPPORT){
            roleType = 'S';
        }
        else{
            roleType = 'T';
        }
    
        printf("%c%d ", roleType, current->level);
        current= current->next;

    }
        

    printf("\n");
}

Champion* removeChampion( Champion *head ){
    // I'm going to check if the linked list is already empty which would be a problem. I do not want this to print 
     if (head == NULL) {
        printf("Empty linked List : \n"); // The list is already empty, nothing to remove
        return NULL;
    }

    // Store the next champion
    Champion* newHead = head->next;

    // Deallocate memory for the current head
    free(head);

    // Return the new head
    return newHead;

}

Champion* destroyChampionList( Champion *head){
    // 10.3 slide 5
    while (head != NULL)
    {
        Champion* t = head;
        head = head->next;
        free(t);
    }

    return NULL;
}





