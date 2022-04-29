#ifndef PROJB_24473_LINKEDLIST_H
#define PROJB_24473_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

// Generic linked list
typedef struct node {
    void *data;
    struct node *next;
}NODE;

/*
 * TODO: validate if it works
 * Adds an element to the end of the linked list
*/
int push(NODE **start, void *data, size_t size){
    NODE *new = NULL, *aux = NULL;
    new = (NODE *) malloc(sizeof(NODE));

    // Out of memory
    if(new == NULL) return -1;

    new->data = malloc(size);
    new->next = NULL;

    // Out of memory
    if(new->data == NULL) return -1;

    /*
     *  If start is NULL, it means that
     *  the linked list is empty
     * */
    if(*start == NULL){
        *start = new;
    }else{
        aux = *start;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new;
    }

    return 0;
}

/*
 * TODO: validate if it works
 * Removes the last element of the linked list
*/
int pop(NODE **start){
    NODE *aux = NULL, *prev = NULL;

    // Empty Linked List
    if(*start == NULL){
        return -1;
    }

    aux = *start;
    // If the start is the only element, remove it
    if(aux->next == NULL){
        *start = NULL;
    }else{
        // Reach the end of the list
        while(aux->next != NULL){
            prev = aux;
            aux = aux->next;
        }
        // Set next pointer to NULL
        prev->next = NULL;
    }

    // Free memory space
    free(aux);
    return 0;
}

/*
 * TODO: validate if it works
 * Returns the size of the linked list
*/
int length(NODE *start){
    NODE *aux = NULL;
    int size = 0;

    aux = start;
    while(aux != NULL){
        size++;
        aux = aux->next;
    }

    return size;
}

/*
 * TODO: validate if it works
 * Deletes all elements of the linked list
*/
void clear(NODE **start){
    NODE *aux = NULL, *next = NULL;

    aux = *start;
    *start = NULL;
    while(aux != NULL){
        next = aux->next;
        free(aux);
        aux = next;
    }
}

#endif //PROJB_24473_LINKEDLIST_H
