#ifndef PROJB_24473_USER_H
#define PROJB_24473_USER_H

#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "LinkedList.h"


typedef enum role{
    decision_maker = 0 ,
    admin = 1
} ROLE;

typedef struct user{
    char username[100];
    char name[100];
    char password[100];
    ROLE role;
}USER;

/* start::{CRUD} */

/*
 * Adds a new user
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int add_user(NODE **start, USER *user) {
    return push(start, user, sizeof(USER));
}

/*
 * Removes a user given a username
 *  - return  0: Success
 *  - return -1: User not found
 *  - return -2: List is empty
*/
int remove_user_by_username(NODE **start, char username[100]){
    NODE *aux = NULL;
    USER *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return -2;

    aux = *start;
    while(aux != NULL){
        data = (USER *) aux->data;
        if(strcmp(data->username, username) == 0){
            return splice(start, index);
        }

        aux = aux->next;
        index++;
    }

    return -1;
}

/* end::{CRUD}*/

/*
 * Finds a user given a username
 *  - Returns the user
 *  - Returns NULL if not found
*/
USER* find_user_by_username(NODE *start, char username[100]){
    NODE *aux = NULL;
    USER *data = NULL;
    int index = 0;

    // Empty list
    if(start == NULL) return NULL;

    aux = start;
    while(aux != NULL){
        data = (USER *) aux->data;
        if(strcmp(data->username, username) == 0){
            return data;
        }

        aux = aux->next;
        index++;
    }

    return NULL;
}

/*
 * Logins the user given username and password
 *  - return  0: Success
 *  - return -1: User not found
 *  - return -2: Wrong password
*/
int login(NODE *start, char username[100], char password[100]){
    USER *result = find_user_by_username(start, username);

    if(result == NULL) return -1;

    if(strcmp(result->password, password) != 0) return -2;

    return 0;
}

/*
 * Prints information of all users
*/
void print_users(NODE *start){
    NODE *aux = NULL;
    USER *data = NULL;


    if(start == NULL){
        printf("Empty list\n");
        return;
    }

    aux = start;
    while(aux != NULL){
        data = (USER*) aux->data;

        printf("Username: %s\n", data->username);
        printf("Name: %s\n", data->name);
        printf("Role: %i\n", data->role);

        aux = aux->next;
    }
}

/*
 * Saves all users to a file
 *  - return  0: Success
 *  - return -1: Error saving
*/
int save_users(NODE *start){
    NODE *aux = NULL;
    int res;

    // Empty the file
    remove(users_filename);

    aux = start;
    while(aux != NULL){
        // Appends data to file
        res = appendToFile(users_filename, aux->data, sizeof (USER));

        // If failed, then delete file.
        if(res != 0) {
            remove(users_filename);
            return -1;
        }

        aux = aux->next;
    }

    return 0;
}

/*
 * Loads users from file
 *  - return  0: Success
 *  - return -3: Error opening file
*/
int load_users(NODE **start){
    int res;

    FILE *fp = fopen(users_filename,"rb");

    if(fp == NULL) return -3;

    do {
        // Allocates memory for the data
        USER *data = (USER*) malloc(sizeof (USER));

        // Reads user data
        res = fread(data, sizeof (USER),1, fp);

        // Didn't read anything, then break the loop
        if(res == 0) break;

        add_user(start, data);
    }while(res != 0);

    fclose(fp);

    return 0;
}

#endif //PROJB_24473_USER_H
