#ifndef PROJB_24473_MENU_H
#define PROJB_24473_MENU_H

#include "user.h"

/*
 * Clears the menu screen
*/
void clear_menu();

/*
 * Prompts the user to press enter to continue
*/
void any_key();

/*
 * Login menu
 *  - return  0: Success
 *  - return -1: Exit program
*/
int auth_menu(NODE *users, USER **auth);

/*
 * Admin menu
 *  - return -4: Sign out
*/
int admin_menu(NODE **users, NODE **budgets, NODE **queue);

/*
 * Listing menu
*/
int budget_listing_menu(NODE **budgets, NODE **queue);

/*
 * Prompts the user for new user info
 *  - return  0: Success
 *  - return -1: Failed to create user
 *  - return -3: Out of memory
*/
int create_user(NODE **users);

/*
 * Prompts the user for new budget info
 *  - return  0: Success
 *  - return -1: Failed to create budget
 *  - return -3: Out of memory
*/
int create_budget(NODE **budgets, NODE **queue);

/*
 * Lists all information about the pending budgets
*/
void list_pending_budgets(NODE *queue);

#endif //PROJB_24473_MENU_H
