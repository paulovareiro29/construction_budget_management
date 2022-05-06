#include "user.h"

int add_user(NODE **start, USER *user) {
    USER* res = find_user_by_username(*start, user->username);
    if(res != NULL) return -1;
    return push(start, user, sizeof(USER));
}

int remove_user_by_username(NODE **start, char username[MAX]){
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

USER* find_user_by_username(NODE *start, char username[MAX]){
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

USER* login(NODE *start, char username[MAX], char password[MAX]){
    USER *result = find_user_by_username(start, username);

    if(result == NULL) return NULL;

    if(strcmp(result->password, password) != 0) {
        return NULL;
    }

    return result;
}

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