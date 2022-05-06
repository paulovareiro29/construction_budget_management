#include <stdio.h>
#include "menu.h"
#include "user.h"
#include "budget.h"

int load(NODE **users, NODE **budgets){

    /* load program from files */
    load_users(users);
    load_budgets(budgets);


    // If user file was empty, populate with root
    if(length(*users) == 0){
        USER root = {"root","root","root",admin};
        add_user(users,&root);
        save_users(*users);
    }

    printf("size: %i", length(*users));

}

int main() {
    NODE *users = NULL;
    NODE *budgets = NULL;

    USER *auth = NULL;

    load(&users, &budgets);

    /*
     * Enters the auth menu aka login menu.
     * returning -1 means that the user wants to exit the program.
     */
    if (auth_menu(users, &auth) == -1) return 0;

    if(auth->role == admin){
        admin_menu(&users, &budgets);
    }else{
        printf("USER MENU");
    }

    printf("Exiting...");

    return 0;
}
