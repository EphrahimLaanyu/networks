#include <stdio.h>
#include <string.h>
#include "user.h"

// Helper function to remove newline from fgets input
void trim_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

/* SEARCH USERS BY USERNAME 
   Uses strstr to find partial matches (e.g., "chen" finds "chengo")
*/
void search_user_by_username() {
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        printf("\nError: Could not open user database.\n");
        return;
    }

    char term[50];
    User temp;
    int found = 0;

    printf("\nEnter username (or part of it) to search: ");
    scanf("%s", term);

    printf("\n--- User Search Results ---\n");
    printf("%-5s | %-20s | %-10s\n", "ID", "Username", "Status");
    printf("------------------------------------------\n");

    while (fread(&temp, sizeof(User), 1, file)) {
        if (strstr(temp.username, term) != NULL) {
            printf("%-5d | %-20s | %-10s\n", 
                   temp.id, 
                   temp.username, 
                   temp.is_active ? "Active" : "Inactive");
            found = 1;
        }
    }

    if (!found) {
        printf("No users found matching '%s'.\n", term);
    }
    
    fclose(file);
}

/* SEARCH MESSAGES BY CONTENT 
   Filters the messages.dat file for a specific keyword
*/
void search_messages_by_keyword() {
    FILE *file = fopen("messages.dat", "rb");
    if (file == NULL) {
        printf("\nNo message database found.\n");
        return;
    }

    char keyword[50];
    Message msg;
    int found = 0;

    printf("\nEnter keyword to search for in messages: ");
    getchar(); // Clear buffer
    fgets(keyword, sizeof(keyword), stdin);
    trim_newline(keyword);

    printf("\n--- Message Search Results ---\n");
    while (fread(&msg, sizeof(Message), 1, file)) {
        if (strstr(msg.message, keyword) != NULL) {
            printf("\n[%s]\n", msg.timestamp);
            printf("From: %d -> To: %d\n", msg.sender_id, msg.receiver_id);
            printf("Content: %s\n", msg.message);
            printf("----------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No messages containing '%s' were found.\n", keyword);
    }

    fclose(file);
}