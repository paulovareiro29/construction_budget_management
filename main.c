#include <stdio.h>
#include "menu.h"
#include "user.h"
#include "budget.h"

int load(NODE **users, NODE **budgets, NODE **queue){

    /* load program from files */
    load_users(users);
    load_budgets(budgets);
    load_queue(*budgets, queue);


    // If user file was empty, populate with root
    if(length(*users) == 0){
        USER root = {"root","root","root",admin};
        USER *data = (USER*) malloc(sizeof (USER));

        if(data != NULL){
            *data = root;
            add_user(users,data);
            save_users(*users);
        }
    }
}

int main() {
    int res = 0;
    NODE *users = NULL;
    NODE *budgets = NULL;
    NODE *queue = NULL;

    USER *auth = NULL;

    load(&users, &budgets, &queue);
    /*
     * while res == -4, it will keep in a loop
     * res == -4, means that user has selected 'sign out' on the menu
    */
    do {
        /*
         * Enters the auth menu aka login menu.
         * returning -1 means that the user wants to exit the program.
         */
        if (initial_menu(users, &auth) == -1) return 0;

        if(auth->role == admin){
            res = admin_menu(*auth, &users, &budgets, &queue);
        }else{
            res = user_menu(*auth,&budgets,&queue);
        }

    }while(res == -4);


    printf("Exiting...");

    return 0;
}
