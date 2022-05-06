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
*/
int admin_menu(NODE **users, NODE **budgets);

int create_user(NODE **users);

#endif //PROJB_24473_MENU_H
