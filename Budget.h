#ifndef PROJB_24473_BUDGET_H
#define PROJB_24473_BUDGET_H

#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "LinkedList.h"

typedef enum state{
    pending = 0,
    analysing = 1,
    finished = 2
} STATE;

typedef enum result{
    awaiting = -1,
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
    int detailsSize;
    STATE state;
    /* when finished */
    RESULT result;
    time_t date;
    char justification[100];
    char user;
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


/*
 * Adds a new detail
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int add_detail(NODE **start, DETAIL *detail){
    return push(start,detail, sizeof (DETAIL));
}

/*
 * Finds a detail given the position
 *  - returns the detail
 *  - returns NULL if not found
*/
DETAIL* find_detail_by_position(NODE *start, int position){
    NODE *aux = NULL;
    DETAIL *data = NULL;
    int index = 0;

    // Empty list
    if(start == NULL) return NULL;

    if(length(start) - 1 < position) return NULL;

    aux = start;
    while(aux != NULL){
        data = (DETAIL *) aux->data;
        if(index == position){
            return data;
        }

        aux = aux->next;
        index++;
    }

    return NULL;
}

/*
 * Removes a detail given the position
 *  - return  0: Success
 *  - return -1: Detail not found
 *  - return -2: List is empty
*/
int remove_detail_by_position(NODE **start, int position){
    NODE *aux = NULL;
    BUDGET *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return -2;

    if(length(start) - 1 < position) return -1;

    aux = *start;
    while(aux != NULL){
        if(index == position) return splice(start, index);

        aux = aux->next;
        index++;
    }

    return -1;
}

/*
 * Saves all budgets to a file
 *  - return  0: Success
 *  - return -1: Error saving
*/
int save_budgets(NODE *start){
    BUDGET *b = NULL;
    NODE *aux, *baux = NULL;
    int res, i;

    // Empty the file
    remove(budgets_filename);

    aux = start;
    while(aux != NULL){
        b = (BUDGET *) aux->data;

        b->detailsSize = length(b->details);

        // Appends data to file
        res = appendToFile(budgets_filename, aux->data, sizeof (BUDGET));

        // If failed, then delete file.
        if(res != 0) {
            remove(budgets_filename);
            return -1;
        }

        baux = b->details;
        while(baux != NULL){
            res = appendToFile(budgets_filename, baux->data, sizeof (DETAIL));

            // If failed, then delete file.
            if(res != 0) {
                remove(budgets_filename);
                return -1;
            }

            baux = baux->next;
        }

        aux = aux->next;
    }

    return 0;
}

/*
 * Load budgets from file
 *  - return  0: Success
 *  - return -3: Error opening file
*/
int load_budgets(NODE **start){
    int res, i;

    FILE *fp = fopen(budgets_filename,"rb");


    if(fp == NULL) return -3;

    do {
        // Allocates memory for the data
        BUDGET *budget_data = (BUDGET *) malloc(sizeof (BUDGET));

        // Reads budget data
        res = fread(budget_data, sizeof (BUDGET),1, fp);

        // Didn't read anything, then break the loop
        if(res == 0) break;

        // Reset pointer
        budget_data->details = NULL;

        add_budget(start, budget_data);

        for(i = 0; i < budget_data->detailsSize; i++){

            // Allocates memory for the data
            DETAIL *detail_data = (DETAIL *) malloc(sizeof (DETAIL));

            // Reads details data
            res = fread(detail_data, sizeof (DETAIL),1, fp);

            // Didn't read anything, then break the loop
            if(res == 0) break;

            add_detail(&budget_data->details, detail_data);
        }
    }while(res != 0);

    fclose(fp);

    return 0;
}
#endif //PROJB_24473_BUDGET_H
