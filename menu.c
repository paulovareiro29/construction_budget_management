#include "menu.h"
#include "budget.h"
#include <conio.h>

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

int auth_menu(NODE *users, USER **auth) {
    char username[MAX], password[MAX];
    int opc = 1;

    clear_menu();
    do {
        printf("Please authenticate before continuing\n");

        printf(" - Username:");
        scanf("%s", username);
        fflush(stdin);

        printf(" - Password:");
        scanf("%s", password);
        fflush(stdin);

        clear_menu();

        *auth = login(users, username, password);
        clear_menu();

        if (*auth != NULL) return 0;

        if (*auth == NULL) {
            do {
                printf("Wrong account credentials!\n [1] Try again!\n [0] Exit\nOption:");
                scanf("%i", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
    } while (*auth == NULL && opc != 0);

    return -1;
}

int admin_menu(NODE **users, NODE **budgets, NODE **queue) {
    int opc;

    do {
        clear_menu();
        printf("MENU\n");
        printf("[ 1 ] Create new user\n");
        printf("[ 2 ] Add budget\n");
        printf("[ 3 ] Listing options\n");
        /*printf("[ 3 ] Update budget\n");
        printf("[ 4 ] Delete budget\n");
        printf("[ 5 ] Find budget\n");*/
        printf("[ 8 ] List all users\n");
        printf("[ 9 ] Sign out\n");
        printf("[ 0 ] Exit\nOption:");
        scanf("%i", &opc);

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

int budget_listing_menu(NODE **budgets, NODE **queue){
    int opc;
    float amount = 0;
    char supplier[MAX];

    do {
        clear_menu();
        printf("BUDGET LISTING MENU\n");
        printf("[ 1 ] List all pending budgets\n");
        printf("[ 2 ] List all finished budgets\n");
        printf("[ 3 ] List all approved budgets\n");
        printf("[ 4 ] List all budgets above given amount\n");
        printf("[ 5 ] List all budgets by supplier\n");
        printf("[ 0 ] Exit\nOption:");
        scanf("%i", &opc);

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
                scanf("%s", supplier);
                list_budgets_by_supplier(*budgets,supplier);
                any_key();
                break;
            default:
                break;
        }

    } while (opc != 0);
}


/* START::{ADMIN FUNCTIONS} */
int create_user(NODE **users) {
    int opc, res;

    USER *user = malloc(sizeof(USER));

    if (user == NULL) return -3;

    do {
        clear_menu();
        printf("NEW USER\n");

        printf(" - Username:");
        scanf("%s", user->username);
        fflush(stdin);

        printf(" - Name:");
        scanf("%s", user->name);
        fflush(stdin);

        printf(" - Password:");
        scanf("%s", user->password);
        fflush(stdin);

        printf(" - Role:\n");
        printf("   [ 0 ] user\n");
        printf("   [ 1 ] admin\nOption:");
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
                    printf("Username already exists!\n");
                    printf("[ 1 ] Try again!\n");
                    printf("[ 0 ] Exit\nOption:");
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

    BUDGET *budget = (BUDGET *) malloc(sizeof(BUDGET));

    if (budget == NULL) return -3;

    budget->total = 0;
    budget->state = pending;
    budget->details = NULL;

    clear_menu();
    printf("NEW BUDGET\n");

    printf(" - Supplier:");
    scanf("%s", budget->supplier);
    fflush(stdin);

    printf(" - Description:");
    scanf("%s", budget->description);
    fflush(stdin);

    do {
        printf(" - Want to add details?\n   [1] Yes\n   [0] No\nOption:");
        scanf("%i", &opc);
        fflush(stdin);
    } while (opc < 0 || opc > 1);

    while (opc != 0) {
        DETAIL *detail = (DETAIL *) malloc(sizeof(DETAIL));

        if (detail == NULL) return -3;

        printf(" - New detail nr%i\n", length(budget->details));

        printf("   - Detail description:");
        scanf("%s", detail->description);
        fflush(stdin);

        printf("   - Quantity:");
        scanf("%d", &detail->quantity);
        fflush(stdin);

        printf("   - Unitary Price:");
        scanf("%f", &detail->price);
        fflush(stdin);

        budget->total += detail->price * detail->quantity;

        res = add_detail(&budget->details, detail);

        if (res != 0) {
            free(detail);
            return res;
        }

        do {
            printf("Want to add more details?\n[ 1 ] Yes\n[ 0 ] No\nOption:");
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
            count++;
        }

        aux = aux->next;
    }

    if(count == 0) printf("No budgets found by supplier: %s!\n", supplier);
}
/* END::{ADMIN FUNCTIONS}*/