#include "menu.h"
#include "budget.h"
#include <conio.h>
#include <time.h>

void clear_menu() {
    int i;
    for (i = 0; i < 5; i++) {
        printf("\n\n\n\n\n");
    }
}

void any_key() {
    printf("\nPress enter to continue...");
    getch();
}

int initial_menu(NODE *users, USER **auth){
    int opc = 1;

    do {
        clear_menu();
        printf("-------------------\n");
        printf("      WELCOME      \n");
        printf("-------------------\n");
        printf("[ 1 ] Authenticate\n");
        printf("[ 0 ] Exit\n\n");
        printf("Option:");
        scanf("%d", &opc);
        fflush(stdin);

        clear_menu();

        if(opc == 1 && auth_menu(users, auth) == 0) return 0;

    }while(opc != 0);

    return -1;
}

int auth_menu(NODE *users, USER **auth) {
    char username[MAX], password[MAX];
    int opc = 1;

    clear_menu();
    do {
        printf("--------------------------\n");
        printf("      AUTHENTICATION      \n");
        printf("--------------------------\n");

        printf("     | Username:");
        scanf("%s", username);
        fflush(stdin);

        printf("     | Password:");
        scanf("%s", password);
        fflush(stdin);

        clear_menu();

        *auth = login(users, username, password);
        clear_menu();

        if (*auth != NULL) return 0;

        if (*auth == NULL) {
            do {
                printf("--------------------------\n");
                printf("      AUTHENTICATION      \n");
                printf("--------------------------\n");
                printf("[1] Try again!\n[0] Exit\n\nOption:");
                scanf("%i", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
    } while (*auth == NULL && opc != 0);

    return -1;
}

int admin_menu(USER auth, NODE **users, NODE **budgets, NODE **queue) {
    int opc;

    do {
        clear_menu();
        printf("----------------------------------------\n");
        printf("               ADMIN MENU               \n");
        printf("----------------------------------------\n");

        printf("[ 1 ] Create new user\n");
        printf("[ 2 ] Add budget\n");
        printf("[ 3 ] Listing options\n");
        printf("[ 4 ] User ranking\n");
        printf("[ 5 ] Save finished budgets to text file\n");
        printf("[ 9 ] Sign out\n");
        printf("[ 0 ] Exit\n\n");
        printf("Option:");
        scanf("%i", &opc);
        fflush(stdin);

        clear_menu();
        switch (opc) {
            case 1:
                create_user(users);
                any_key();
                break;
            case 2:
                create_budget(budgets, queue);
                any_key();
                break;
            case 3:
                budget_listing_menu(budgets, queue);
                break;
            case 4:
                list_user_ranking(*users, *budgets);
                any_key();
                break;
            case 5:
                save_finished_budgets(*budgets);
                any_key();
                break;
            case 8:
                print_users(*users);
                any_key();
                break;
            case 9:
                return -4;
            default:
                break;
        }

    } while (opc != 0);
}

int user_menu(USER auth, NODE **budgets, NODE **queue){
    int opc;

    do {
        clear_menu();
        printf("----------------------\n");
        printf("       USER MENU      \n");
        printf("----------------------\n");
        printf("[ 1 ] Analyse budget\n");
        printf("[ 9 ] Sign out\n");
        printf("[ 0 ] Exit\n\n");
        printf("Option:");
        scanf("%i", &opc);
        fflush(stdin);
        clear_menu();

        switch (opc) {
            case 1:
                analyse_budget(auth,budgets,queue);
                any_key();
                break;
            case 9:
                return -4;
            default:
                break;
        }

    } while (opc != 0);
}

int budget_listing_menu(NODE **budgets, NODE **queue){
    int opc;
    float amount = 0;
    char string[MAX];

    do {
        clear_menu();
        printf("-----------------------------------------------\n");
        printf("               BUDGET LISTING MENU             \n");
        printf("-----------------------------------------------\n");
        printf("[ 1 ] List all pending budgets\n");
        printf("[ 2 ] List all finished budgets\n");
        printf("[ 3 ] List all approved budgets\n");
        printf("[ 4 ] List all budgets above given amount\n");
        printf("[ 5 ] List all budgets by supplier\n");
        printf("[ 6 ] List all finished budgets by certain user\n");
        printf("[ 0 ] Exit\n\n");
        printf("Option:");
        scanf("%i", &opc);
        clear_menu();

        switch (opc) {
            case 1:
                list_pending_budgets(*queue);
                any_key();
                break;
            case 2:
                list_finished_budgets(*budgets);
                any_key();
                break;
            case 3:
                list_approved_budgets(*budgets);
                any_key();
                break;
            case 4:
                printf("Enter the amount:");
                scanf("%f", &amount);
                list_budgets_above_amount(*budgets, amount);
                any_key();
                break;
            case 5:
                printf("Enter the supplier:");
                scanf("%s", string);
                list_budgets_by_supplier(*budgets,string);
                any_key();
                break;
            case 6:
                printf("Enter the username:");
                scanf("%s", string);
                list_finished_budgets_by_user(*budgets, string);
                any_key();
                break;
            default:
                break;
        }

    } while (opc != 0);
}

// START::{ADMIN FUNCTIONS}

int create_user(NODE **users) {
    int opc, res;

    USER *user = malloc(sizeof(USER));

    if (user == NULL) return -3;

    do {
        clear_menu();
        printf("----------------------\n");
        printf("       NEW USER       \n");
        printf("----------------------\n");

        printf(" | Username:");
        scanf("%s", user->username);
        fflush(stdin);

        printf(" | Name:");
        scanf("%s", user->name);
        fflush(stdin);

        printf(" | Password:");
        scanf("%s", user->password);
        fflush(stdin);

        printf(" | Role: (0) - user | (1) - admin\n");
        printf("   Option:");
        scanf("%i", &user->role);
        fflush(stdin);

        res = add_user(users, user);

        switch (res) {
            case 0:
                save_users(*users);
                printf("User created successfully!");
                return 0;
            case -1:
                do {
                    clear_menu();
                    printf("-------------------------------------\n");
                    printf("       USERNAME ALREADY EXISTS       \n");
                    printf("-------------------------------------\n");
                    printf("[ 1 ] Try again!\n");
                    printf("[ 0 ] Exit\n\n");
                    printf("Option:");
                    scanf("%i", &opc);
                } while (opc < 0 || opc > 1);
                break;
            default:
                break;
        }

    } while (opc != 0);

    free(user);
    return -1;
}

int create_budget(NODE **budgets, NODE **queue) {
    int opc, res;
    NODE *aux = NULL;
    DETAIL *detail = NULL;
    BUDGET *budget = (BUDGET *) malloc(sizeof(BUDGET));

    if (budget == NULL) return -3;

    budget->total = 0;
    budget->state = pending;
    budget->details = NULL;

    printf("------------------------\n");
    printf("       NEW BUDGET       \n");
    printf("------------------------\n");

    printf(" | Supplier:");
    scanf("%s", budget->supplier);
    fflush(stdin);

    printf(" | Description:");
    scanf("%s", budget->description);
    fflush(stdin);

    do {
        printf(" | Want to add details? (1) - yes | (0) - no\n");
        printf("   Option:");
        scanf("%i", &opc);
        fflush(stdin);
    } while (opc < 0 || opc > 1);

    while (opc != 0) {

        res = create_detail(&budget->details);

        if(res == -2) break;

        if(res != 0)
            return res;

        aux = last_node(budget->details);

        if(aux == NULL) break;

        detail = (DETAIL*) aux->data;
        budget->total += detail->price * detail->quantity;

        do {
            printf(" | Want to add more details? (1) - yes | (0) - no\n");
            printf("   Option:");
            scanf("%i", &opc);
            fflush(stdin);
        } while (opc < 0 || opc > 1);
    }

    res = add_budget(budgets, budget);
    add_budget(queue, budget);

    if (res != 0) {
        free(budget);
        return res;
    }

    save_budgets(*budgets);
    printf("Budget created successfully!");
    return 0;
}

int create_detail(NODE **details){
    int res = 0;

    if(length(*details) >= 20) {
        printf("Maximum details reached!\n");
        return -2;
    }

    DETAIL *detail = (DETAIL *) malloc(sizeof(DETAIL));

    if (detail == NULL) return -3;

    printf("-----------------------------\n");
    printf("       NEW DETAIL NR%i       \n", length(*details));
    printf("-----------------------------\n");
    printf("   | Detail description:");
    scanf("%s", detail->description);
    fflush(stdin);

    printf("   | Quantity:");
    scanf("%d", &detail->quantity);
    fflush(stdin);

    printf("   | Unitary Price:");
    scanf("%f", &detail->price);
    fflush(stdin);

    res = add_detail(details, detail);

    if (res != 0) {
        free(detail);
        return res;
    }

    return 0;
}

void list_pending_budgets(NODE *queue){
    NODE *aux = NULL;
    BUDGET *budget_data = NULL;

    if(queue == NULL){
        printf("No pending budgets found!\n");
        return;
    }

    aux = queue;
    while(aux != NULL){
        budget_data = (BUDGET*) aux->data;

        print_budget(budget_data);
        printf("\n");
        aux = aux->next;
    }
}

void list_finished_budgets(NODE *budgets){
    int count = 0;
    NODE *aux = NULL;
    BUDGET *budget_data = NULL;


    aux = budgets;
    while(aux != NULL){
        budget_data = (BUDGET*) aux->data;

        if(budget_data->state == finished){
            print_budget(budget_data);
            printf("\n");
            count++;
        }

        aux = aux->next;
    }

    if(count == 0) printf("No finished budgets found!\n");
}

void list_approved_budgets(NODE *budgets){
    int count = 0;
    NODE *aux = NULL;
    BUDGET *budget_data = NULL;


    aux = budgets;
    while(aux != NULL){
        budget_data = (BUDGET*) aux->data;

        if(budget_data->state == finished && budget_data->result == approved){
            print_budget(budget_data);
            printf("\n");
            count++;
        }

        aux = aux->next;
    }

    if(count == 0) printf("No finished and approved budgets found!\n");
}

void list_budgets_above_amount(NODE *budgets, float amount){
    int count = 0;
    NODE *aux = NULL;
    BUDGET *budget_data = NULL;


    aux = budgets;
    while(aux != NULL){
        budget_data = (BUDGET*) aux->data;

        if(budget_data->total > amount){
            print_budget(budget_data);
            printf("\n");
            count++;
        }

        aux = aux->next;
    }

    if(count == 0) printf("No budgets found with total above %.2f$!\n", amount);
}

void list_budgets_by_supplier(NODE *budgets, char supplier[MAX]){
    int count = 0;
    NODE *aux = NULL;
    BUDGET *budget_data = NULL;


    aux = budgets;
    while(aux != NULL){
        budget_data = (BUDGET*) aux->data;

        if(strcmp(budget_data->supplier, supplier) == 0){
            print_budget(budget_data);
            printf("\n");
            count++;
        }

        aux = aux->next;
    }

    if(count == 0) printf("No budgets found by supplier: %s!\n", supplier);
}

void list_user_ranking(NODE *users, NODE *budgets){
    NODE *aux = NULL;
    RANKING *ranking = NULL, temp;
    int size = 0, i, j, pos = 0;

    /* Counts how many users there is */
    aux = users;
    while(aux != NULL){
        USER *data = (USER *) aux->data;

        if(data->role == decision_maker) size++;
        aux = aux->next;
    }

    if(size == 0){
        printf("Ranking is empty!");
        return;
    }

    ranking = (RANKING *) calloc(size, sizeof (RANKING));

    /* Populate the array with all users */
    aux = users;
    while(aux != NULL){
        USER *data = (USER *) aux->data;

        if(data->role == decision_maker){
            strcpy(ranking[pos].username, data->username);
            ranking[pos].score = 0;
            pos++;
        }

        aux = aux->next;
    }

    /* Iterate through the budgets list */
    aux = budgets;
    while(aux != NULL){
        BUDGET *data = (BUDGET *) aux->data;

        if(data->state == finished){
            /* Loop through all the ranking array */
            for(i = 0; i < pos; i++){
                /* When user found, increment the score */
                if(strcmp(ranking[i].username, data->user) == 0 ){
                    ranking[i].score++;
                    break;
                }
            }
        }

        aux = aux->next;
    }

    // Insertion sort
    for(i = 1; i < pos; i++){
        temp = ranking[i];
        j = i - 1;
        while(j >= 0 && ranking[j].score < temp.score){
            ranking[j + 1] = ranking[j];
            j--;
        }

        ranking[j + 1] = temp;
    }

    printf("--------------------------\n");
    printf("       USER RANKING       \n");
    printf("--------------------------\n");
    for(i = 0; i < pos; i++){
        printf("%i: %i - %s\n", i + 1, ranking[i].score, ranking[i].username);
    }

    free(ranking);
}

void list_finished_budgets_by_user(NODE *budgets, char username[MAX]){
    NODE *aux = NULL;
    BUDGET *list = NULL, temp;
    int size = 0, i, j, pos = 0;

    /* Counts how many finished budgets there is */
    aux = budgets;
    while(aux != NULL){
        BUDGET *data = (BUDGET *) aux->data;

        if(data->state == finished && strcmp(data->user, username) == 0) size++;
        aux = aux->next;
    }

    if(size == 0){
        printf("List is empty!");
        return;
    }

    list = (BUDGET *) calloc(size, sizeof (BUDGET));

    /* Populate the array with all budgets */
    aux = budgets;
    while(aux != NULL){
        BUDGET *data = (BUDGET *) aux->data;

        if(data->state == finished  && strcmp(data->user, username) == 0){
            list[pos] = *data;
            pos++;
        }

        aux = aux->next;
    }


    // Insertion sort - date
    for(i = 1; i < pos; i++){
        temp = list[i];
        j = i - 1;
        while(j >= 0 && list[j].date > temp.date){
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = temp;
    }

    // Insertion sort - result
    for(i = 1; i < pos; i++){
        temp = list[i];
        j = i - 1;
        while(j >= 0 && list[j].result > temp.result){
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = temp;
    }


    printf("--------------------------\n");
    printf("          BUDGETS         \n");
    printf("--------------------------\n");
    for(i = 0; i < pos; i++){
        print_budget(&list[i]);
        printf("\n");
    }

    free(list);
}

int save_finished_budgets(NODE *budgets){
    NODE *aux = NULL;
    DETAIL *detail = NULL;
    BUDGET *list = NULL, temp;
    int size = 0, i, j, pos = 0;

    FILE *fp = fopen(finished_budgets_filename, "w");

    if(fp == NULL) return -3;

    /* Counts how many finished budgets there is */
    aux = budgets;
    while(aux != NULL){
        BUDGET *data = (BUDGET *) aux->data;

        if(data->state == finished) size++;
        aux = aux->next;
    }

    if(size == 0){
        printf("List is empty!");
        fprintf(fp,"");
        return 0;
    }

    list = (BUDGET *) calloc(size, sizeof (BUDGET));

    /* Populate the array with all budgets */
    aux = budgets;
    while(aux != NULL){
        BUDGET *data = (BUDGET *) aux->data;

        if(data->state == finished){
            list[pos] = *data;
            pos++;
        }

        aux = aux->next;
    }


    // Insertion sort - amount
    for(i = 1; i < pos; i++){
        temp = list[i];
        j = i - 1;
        while(j >= 0 && list[j].total > temp.total){
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = temp;
    }

    for(i = 0; i < pos; i++){
        temp = list[i];

        fprintf(fp,"------- BUDGET -------\n");
        fprintf(fp," |- ID: %i\n", temp.id);
        fprintf(fp," |- Supplier: %s\n", temp.supplier);
        fprintf(fp," |- Description: %s\n", temp.description);
        fprintf(fp," | Total: %.2f$\n", temp.total);

        switch (temp.state) {
            case 0:
                fprintf(fp," |- State: Pending\n");
                break;
            case 1:
                fprintf(fp," |- State: Analysing\n");
                break;
            case 2:
                fprintf(fp," |- State: Finished\n");
                break;
        }

        aux = temp.details;

        if(aux == NULL){
            fprintf(fp," |- Details list empty!\n");
        }else{
            fprintf(fp," |- Details list:\n");
            while(aux != NULL){
                detail = (DETAIL*) aux->data;

                fprintf(fp,"  |- Item:\n");
                fprintf(fp,"     |- Description: %s\n", detail->description);
                fprintf(fp,"     |- Quantity: %d\n", detail->quantity);
                fprintf(fp,"     |- Unitary price: %.2f$\n", detail->price);

                aux = aux->next;
            }
        }

        switch (temp.result) {
            case -1:
                break;
            case 0:
                fprintf(fp," |- Result: Denied\n");
                break;
            case 1:
                fprintf(fp," |- Result: Approved\n");
                break;
        }

        fprintf(fp," |- Date: %s\n", asctime(gmtime(&temp.date)));
        fprintf(fp," |- Justification: %s\n", temp.justification);
        fprintf(fp," |- User that analysed: %s\n", temp.user);
        fprintf(fp,"\n\n");
    }



    free(list);
    fclose(fp);
    return 0;
}
// END::{ADMIN FUNCTIONS}

// START::{USER FUNCTIONS}

void analyse_budget(USER auth,NODE **budgets, NODE **queue){
    int result;
    char justification[MAX];

    if(*queue == NULL) {
        printf("Queue is empty!");
        return;
    }

    BUDGET *budget = (BUDGET*) (*queue)->data;

    print_budget(budget);

    budget->state = analysing;

    do{
        printf(" | Final result: (1) approved | (0) denied\n");
        printf("   Option:");
        scanf("%i", &result);
        fflush(stdin);
    }while(result < 0 || result > 1);

    printf(" | Justification:");
    gets(justification);
    fflush(stdin);

    budget->result = result;
    strcpy(budget->justification, justification);
    strcpy(budget->user ,auth.username);
    budget->date = time(NULL);
    budget->state = finished;

    shift(queue);
    save_budgets(*budgets);
}

// END::{USER FUNCTIONS}