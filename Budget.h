#ifndef PROJB_24473_BUDGET_H
#define PROJB_24473_BUDGET_H

#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

typedef enum state{
    pending = 0,
    analysing = 1,
    finished = 2
} STATE;

typedef enum result{
    denied = 0,
    approved = 1
} RESULT;

typedef struct detail {
    char description[100];
    int quantity;
    float price;
} DETAIL;

typedef struct budget {
    int id;
    char supplier[100];
    char description[100];
    float total;
    NODE *details;
    STATE state;
    /* when finished */
    RESULT *result;
    time_t *date;
    char *justification[100];
    char *user;
} BUDGET;

/*
 * Adds a new budget
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int add_budget(NODE **start, BUDGET *budget){
    return push(start,budget, sizeof (BUDGET));
}

/*
 * Finds a budget given the id
 *  - returns the budget
 *  - returns NULL if not found
*/
BUDGET* find_budget_by_id(NODE *start, int id){
    NODE *aux = NULL;
    BUDGET *data = NULL;
    int index = 0;

    // Empty list
    if(start == NULL) return NULL;

    aux = start;
    while(aux != NULL){
        data = (BUDGET *) aux->data;
        if(data->id == id){
            return data;
        }

        aux = aux->next;
        index++;
    }

    return NULL;
}

/*
 * Removes a budget given the id
 *  - return  0: Success
 *  - return -1: Budget not found
 *  - return -2: List is empty
*/
int remove_budget_by_id(NODE **start, int id){
    NODE *aux = NULL;
    BUDGET *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return -2;


    aux = *start;
    while(aux != NULL){
        data = (BUDGET *) aux->data;
        if(data->id == id){
            return splice(start, index);
        }

        aux = aux->next;
        index++;
    }

    return -1;
}


#endif //PROJB_24473_BUDGET_H
