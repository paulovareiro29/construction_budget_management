#include "menu.h"
#include <conio.h>

void clear_menu(){
    int i;
    for(i = 0; i < 5; i++){
        printf("\n\n\n\n\n");
    }
}

void any_key(){
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
        scanf("%s",username);
        fflush(stdin);

        printf(" - Password:");
        scanf("%s",password);
        fflush(stdin);

        clear_menu();

        *auth = login(users, username, password);
        clear_menu();

        if(*auth != NULL) return 0;

        if(*auth == NULL) {
            do {
                printf("Wrong account credentials!\n[ 1 ] Try again!\n[ 0 ] Exit\nOption:");
                scanf("%i", &opc);
                fflush(stdin);
                clear_menu();
            } while (opc < 0 || opc > 1);
        }
    }while(*auth == NULL && opc != 0);

    return -1;
}

int admin_menu(NODE **users, NODE **budgets){
    int opc;

    do{
        clear_menu();
        printf("MENU\n");
        printf("[ 1 ] Create new user\n");
        /*printf("[ 2 ] Add budget\n");
        printf("[ 3 ] Update budget\n");
        printf("[ 4 ] Delete budget\n");
        printf("[ 5 ] Find budget\n");*/
        printf("[ 0 ] Exit\nOption:");
        scanf("%i",&opc);

        switch (opc) {
            case 1:
                create_user(users);
                any_key();
                break;
            case 2:
                print_users(*users);
                any_key();
                break;
            default:
                break;
        }

    }while(opc != 0);
}


int create_user(NODE **users){
    int opc, res;

    USER *user = malloc(sizeof (USER));

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
                return 0;
            case -1:
                do {
                    clear_menu();
                    printf("Username already exists!\n");
                    printf("[ 1 ] Try again!\n");
                    printf("[ 0 ] Exit\nOption:");
                    scanf("%i", &opc);
                }while(opc < 0 || opc > 1);
                break;
        }

    }while(opc != 0);

    free(user);
    return -1;
}