// main.c
#include <stdio.h>
#include "user.h"   // Gives access to User struct and all declared functions


int main() {

    int choice;

    do {

        printf("\n--- Main Menu ---\n");
        printf("1. Register User\n");
        printf("2. View Users\n");
        printf("3. Send Message\n");
        printf("4. View Messages\n");
        printf("5. Exit\n");
        printf("6. Search Users\n");
        printf("7. Search Messages\n");
        printf("Choose an option: ");

        scanf("%d", &choice);


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
            
            case 6:
                search_user_by_username();
                break;
                
            case 7:
                search_messages_by_keyword();    

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 5);

    return 0;
}