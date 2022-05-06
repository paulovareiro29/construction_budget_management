#ifndef PROJB_24473_USER_H
#define PROJB_24473_USER_H

#include <string.h>
#include "linkedlist.h"

typedef enum role{
    decision_maker = 0 ,
    admin = 1
} ROLE;

typedef struct user{
    char username[MAX];
    char name[MAX];
    char password[MAX];
    ROLE role;
}USER;

/*
 * Adds a new user
 *  - return  0: Success
 *  - return -1: Username already exists
 *  - return -3: Out of memory
*/
int add_user(NODE **start, USER *user);

/*
 * Removes a user given a username
 *  - return  0: Success
 *  - return -1: User not found
 *  - return -2: List is empty
*/
int remove_user_by_username(NODE **start, char username[MAX]);

/*
 * Finds a user given a username
 *  - Returns the user
 *  - Returns NULL if not found
*/
USER* find_user_by_username(NODE *start, char username[MAX]);

/*
 * Logins the user given username and password
 *  - Returns the user
 *  - Returns NULL if not found
*/
USER* login(NODE *start, char username[MAX], char password[MAX]);

/*
 * Prints information of all users
*/
void print_users(NODE *start);

/*
 * Saves all users to a file
 *  - return  0: Success
 *  - return -1: Error saving
*/
int save_users(NODE *start);

/*
 * Loads users from file
 *  - return  0: Success
 *  - return -3: Error opening file
*/
int load_users(NODE **start);

/*
 * Prompts the admin to create a new user
*/
int create_user(NODE **users);

#endif //PROJB_24473_USER_H
