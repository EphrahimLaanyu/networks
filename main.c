// main.c
#include <stdio.h>
#include "user.h" // Import our custom header to use the functions

int main() {
    int choice;
    
    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Register User\n");
        printf("2. View Users\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            register_user();
        } else if (choice == 2) {
            view_users();
        } else if (choice != 3) {
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 3);

    printf("\nExiting program...\n");
    return 0;
}