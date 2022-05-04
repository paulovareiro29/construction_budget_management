#ifndef PROJB_24473_USER_H
#define PROJB_24473_USER_H

#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

typedef enum role{
    decisor = 0 ,
    administrador = 1
} ROLE;

typedef struct user{
    char username[100];
    char name[100];
    char password[100];
    ROLE role;
}USER;

/* start::{CRUD} */

/*
 * TODO: validate if it works
 * Adds a new user
 *  - return  0: Success
 *  - return -3: Out of memory
 * */
int user_add(NODE **start, USER user) {
    return push(start, &user, sizeof(USER));
}

/*
 * TODO: validate if it works
 * Removes an user given an username
 *  - return  0: Success
 *  - return -1: User not found
 *  - return -2: List is empty
*/
int user_remove_by_username(NODE **start, char username){
    NODE *aux = NULL;
    USER *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return -2;

    aux = *start;
    while(aux != NULL){
        data = (USER *) aux->data;
        if(strcmp(data->username, username) == 0){
            return splice(&start, index);
        }

        aux = aux->next;
        index++;
    }

    return -1;
}

/* end::{CRUD}*/

/*
 * TODO: validate if it works
 * Finds a user given an username
 *  - Returns the user
 *  - Returns NULL if not found
*/
USER* find_user_by_username(NODE **start, char username){
    NODE *aux = NULL;
    USER *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return NULL;

    aux = *start;
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
 * TODO: validate if it works
 * Logins the user given username and password
 *  - return -1: User not found
 *  - return -2: Wrong password
*/
int login_user(NODE **start, char username, char password){
    USER *result = find_user_by_username(start, username);

    if(result == NULL) return -1;

    if(strcmp(result->password, password) != 0) return -2;

    return 0;
}

#endif //PROJB_24473_USER_H
