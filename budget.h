#ifndef PROJB_24473_BUDGET_H
#define PROJB_24473_BUDGET_H

#include "linkedlist.h"

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
    char description[MAX];
    int quantity;
    float price;
} DETAIL;

typedef struct budget {
    int id;
    char supplier[MAX];
    char description[MAX];
    float total;
    NODE *details;
    int detailsSize;
    STATE state;
    /* when finished */
    RESULT result;
    time_t date;
    char justification[MAX];
    char user[MAX];
} BUDGET;

/*
 * Adds a new budget
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int add_budget(NODE **start, BUDGET *budget);

/*
 * Finds a budget given the id
 *  - returns the budget
 *  - returns NULL if not found
*/
BUDGET* find_budget_by_id(NODE *start, int id);

/*
 * Removes a budget given the id
 *  - return  0: Success
 *  - return -1: Budget not found
 *  - return -2: List is empty
*/
int remove_budget_by_id(NODE **budgets, NODE **queue, int id);

/*
 * Adds a new detail
 *  - return  0: Success
 *  - return -1: Maximum details reached
 *  - return -3: Out of memory
*/
int add_detail(NODE **start, DETAIL *detail);

/*
 * Finds a detail given the position
 *  - returns the detail
 *  - returns NULL if not found
*/
DETAIL* find_detail_by_position(NODE *start, int position);

/*
 * Calculates budget total given certain budget as parameter
*/
int calculate_budget_total(BUDGET *budget);

/*
 * Removes a detail given the position
 *  - return  0: Success
 *  - return -1: Detail not found
 *  - return -2: List is empty
*/
int remove_detail_by_position(NODE **start, int position);

/*
 * Saves all budgets to a file
 *  - return  0: Success
 *  - return -1: Error saving
*/
int save_budgets(NODE *start);

/*
 * Load budgets from file
 *  - return  0: Success
 *  - return -3: Error opening file
*/
int load_budgets(NODE **budgets);

int load_queue(NODE *budgets, NODE **queue);

void print_budget(BUDGET *budget);

#endif //PROJB_24473_BUDGET_H
