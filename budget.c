#include <time.h>
#include "budget.h"

int add_budget(NODE **start, BUDGET *budget){
    NODE *aux = NULL;
    BUDGET *temp = NULL;

    if(*start == NULL){
        budget->id = 0;
    }else{
        aux = *start;
        while(aux->next != NULL){
            aux = aux->next;
        }

        temp = (BUDGET *) aux->data;
        budget->id = temp->id + 1;
    }

    return push(start,budget, sizeof (BUDGET));
}

BUDGET* find_budget_by_id(NODE *start, int id){
    NODE *aux = NULL;
    BUDGET *data = NULL;
    int index = 0;

    // Empty list
    if(start == NULL) return NULL;

    aux = start;
    while(aux != NULL){
        data = (BUDGET *) aux->data;
        if(data->id == id){
            return data;
        }

        aux = aux->next;
        index++;
    }

    return NULL;
}

int remove_budget_by_id(NODE **start, int id){
    NODE *aux = NULL;
    BUDGET *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return -2;


    aux = *start;
    while(aux != NULL){
        data = (BUDGET *) aux->data;
        if(data->id == id){
            return splice(start, index);
        }

        aux = aux->next;
        index++;
    }

    return -1;
}

int add_detail(NODE **start, DETAIL *detail){
    return push(start,detail, sizeof (DETAIL));
}

DETAIL* find_detail_by_position(NODE *start, int position){
    NODE *aux = NULL;
    DETAIL *data = NULL;
    int index = 0;

    // Empty list
    if(start == NULL) return NULL;

    if(length(start) - 1 < position) return NULL;

    aux = start;
    while(aux != NULL){
        data = (DETAIL *) aux->data;
        if(index == position){
            return data;
        }

        aux = aux->next;
        index++;
    }

    return NULL;
}

int remove_detail_by_position(NODE **start, int position){
    NODE *aux = NULL;
    BUDGET *data = NULL;
    int index = 0;

    // Empty list
    if(*start == NULL) return -2;

    if(length(start) - 1 < position) return -1;

    aux = *start;
    while(aux != NULL){
        if(index == position) return splice(start, index);

        aux = aux->next;
        index++;
    }

    return -1;
}

int save_budgets(NODE *start){
    BUDGET *b = NULL;
    NODE *aux, *baux = NULL;
    int res, i;

    // Empty the file
    remove(budgets_filename);

    aux = start;
    while(aux != NULL){
        b = (BUDGET *) aux->data;

        b->detailsSize = length(b->details);

        // Appends data to file
        res = appendToFile(budgets_filename, aux->data, sizeof (BUDGET));

        // If failed, then delete file.
        if(res != 0) {
            remove(budgets_filename);
            return -1;
        }

        baux = b->details;
        while(baux != NULL){
            res = appendToFile(budgets_filename, baux->data, sizeof (DETAIL));

            // If failed, then delete file.
            if(res != 0) {
                remove(budgets_filename);
                return -1;
            }

            baux = baux->next;
        }

        aux = aux->next;
    }

    return 0;
}

int load_budgets(NODE **budgets, NODE **queue){
    int res, i;

    FILE *fp = fopen(budgets_filename,"rb");

    if(fp == NULL) return -3;

    do {
        // Allocates memory for the data
        BUDGET *budget_data = (BUDGET *) malloc(sizeof (BUDGET));

        // Reads budget data
        res = fread(budget_data, sizeof (BUDGET),1, fp);

        // Didn't read anything, then break the loop
        if(res == 0) break;

        // Reset pointer
        budget_data->details = NULL;

        add_budget(budgets, budget_data);

        if(budget_data->state == pending) add_budget(queue, budget_data);

        for(i = 0; i < budget_data->detailsSize; i++){

            // Allocates memory for the data
            DETAIL *detail_data = (DETAIL *) malloc(sizeof (DETAIL));

            // Reads details data
            res = fread(detail_data, sizeof (DETAIL),1, fp);

            // Didn't read anything, then break the loop
            if(res == 0) break;

            add_detail(&budget_data->details, detail_data);
        }
    }while(res != 0);

    fclose(fp);

    return 0;
}

void print_budget(BUDGET *budget){
    NODE *aux = NULL;
    DETAIL *detail = NULL;

    printf("BUDGET INFO\n");
    printf("\t- ID: %i\n", budget->id);
    printf("\t- Supplier: %s\n", budget->supplier);
    printf("\t- Description: %s\n", budget->description);
    printf("\t- Total: %.2f$\n", budget->total);

    switch (budget->state) {
        case 0:
            printf("\t- State: Pending\n");
            break;
        case 1:
            printf("\t- State: Analysing\n");
            break;
        case 2:
            printf("\t- State: Finished\n");
            break;
    }

    aux = budget->details;

    if(aux == NULL){
        printf("\t- Details list empty!\n");
    }else{
        printf("\t- Details list:\n");
        while(aux != NULL){
            detail = (DETAIL*) aux->data;

            printf("\t\t- Item:\n");
            printf("\t\t  - Description: %s\n", detail->description);
            printf("\t\t  - Quantity: %d\n", detail->quantity);
            printf("\t\t  - Unitary price: %.2f$\n", detail->price);

            aux = aux->next;
        }
    }

    if(budget->state != finished) return;

    switch (budget->result) {
        case -1:
            break;
        case 0:
            printf("\t- Result: Denied\n");
            break;
        case 1:
            printf("\t- Result: Approved\n");
            break;
    }

    printf("\t- Date: %s\n", asctime(gmtime(&budget->date)));
    printf("\t- Justification: %s\n", budget->justification);
    printf("\t- User that analysed: %s\n", budget->user);
}