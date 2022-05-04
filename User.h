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

/* CRUD FUNCTIONS */

/*
 * TODO: validate if it works
 * Adds a new user
 * */
int user_add(NODE **start, USER user) {
    return push(start, &user, sizeof(USER));
}

/*
 * TODO: validate if it works
 * Removes an user
*/
int user_remove_by_username(NODE **start, char username){
    NODE *aux = NULL;
    USER *data = NULL;
    int index = 0;

    // List is empty, so cannot remove anything
    if(*start == NULL) return -1;

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


#endif //PROJB_24473_USER_H
