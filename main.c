// main.c
#include <stdio.h>
#include "user.h"   // Gives access to User struct and all declared functions

int main() {
    int choice;

    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Register User\n");
        printf("2. View Users\n");
        printf("3. Deregister User\n");
        printf("4. Send Message\n");
        printf("5. View Messages\n");
        printf("6. Search Users\n");
        printf("7. Search Messages\n");
        printf("8. Exit\n");
        printf("Choose an option: ");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                register_user();
                break;
            case 2:
                view_users();
                break;
            case 3:
                deregister_user();
                break;
            case 4:
                send_message();
                break;
            case 5:
                view_messages();
                break;
            case 6:
                search_user_by_username();
                break;
            case 7:
                search_messages_by_keyword();    
                break; 
            case 8:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 8);

    return 0;
}