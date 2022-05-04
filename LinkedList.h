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
 * Adds an element to the end of the linked list
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int push(NODE **start, void *data, size_t size){
    NODE *new = NULL, *aux = NULL;
    new = (NODE *) malloc(sizeof(NODE));

    // Out of memory
    if(new == NULL) return -3;

    new->data = malloc(size);

    // Out of memory
    if(new->data == NULL) return -3;

    new->data = data;
    new->next = NULL;

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
 * Removes the last element of the linked list
 *  - return  0: Success
 *  - return -2: Empty list
*/
int pop(NODE **start){
    NODE *aux = NULL, *prev = NULL;

    // Empty Linked List
    if(*start == NULL){
        return -2;
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
 * Adds an element to the start of the linked list
 *  - return  0: Success
 *  - return -3: Out of memory
*/
int unshift(NODE **start, void *data, size_t size){
    NODE *new = NULL;
    new = (NODE *) malloc(sizeof (NODE));

    // Out of memory
    if(new == NULL) return -3;

    new->data = malloc(size);

    // Out of memory
    if(new->data == NULL) return -3;

    new->data = data;
    new->next = NULL;

    if(*start != NULL){
        new->next = *start;
    }

    *start = new;
    return 0;
}

/*
 * Removes the first element of the linked list
 *  - return  0: Success
 *  - return -2: List is empty
*/
int shift(NODE **start){
    NODE *aux = *start;

    // Empty Linked List
    if(aux == NULL) return -2;

    *start = aux->next;
    free(aux);
    return 0;
}

/*
 * Removes an element given an index
 *  - return  0: Success
 *  - return -1: Element not found
 *  - return -2: List is empty
*/
int splice(NODE **start, int index){
    NODE *aux = NULL, *prev = NULL;
    int size = 0;


    // Empty linked list
    if(*start == NULL) return -2;

    aux = *start;

    while(aux != NULL && size != index){
        prev = aux;
        aux = aux->next;
        size++;
    }

    // If size != index then the index doesn't exist
    if(size != index) return -1;

    /* If the previous element is null it means that the element found
     * is the first of the list, so the start must point to the next
     * */
    if(prev == NULL){
        *start = aux->next;
    }else{
        prev->next = aux->next;
    }

    /* If the next of the element found is null
     * it means that it is the last element of the list,
     * so the previous elements points to NULL.
     *
     * Else it is in the middle, so the previous
     * element must point to the next of the element found.
     * */

    free(aux);
    return 0;
}

/*
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
