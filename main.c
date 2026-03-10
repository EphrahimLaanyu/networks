// main.c
#include <stdio.h>
#include "user.h"   // Gives access to User struct and all declared functions

/*
-------------------------------------------------------
MAIN FUNCTION
-------------------------------------------------------
This is the main entry point of the program.

The menu allows users to:
1. Register new users
2. View all registered users
3. Search for a user
4. Send messages
5. View messages
6. Exit the program
*/

int main() {

    int choice;

    do {

        printf("\n--- Main Menu ---\n");
        printf("1. Register User\n");
        printf("2. View Users\n");
        printf("3. Send Message\n");
        printf("4. View Messages\n");
        printf("5. Exit\n");
        printf("Choose an option: ");

        scanf("%d", &choice);

        /*
        -------------------------------------------------------
        SWITCH MENU LOGIC
        -------------------------------------------------------
        Each menu option calls a different function
        implemented in separate modules.
        */

        switch(choice) {

            case 1:
                // Calls function from register.c
                register_user();
                break;

            case 2:
                // Displays all users from users.dat
                view_users();
                break;
            case 3:
                // Sends a message and saves to messages.dat
                send_message();
                break;

            case 4:
                // Displays all stored messages
                view_messages();
                break;

            case 5:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 5);

    return 0;
}