// register.c
#include <stdio.h>
#include <string.h>
#include "user.h" // Import our custom header!

void register_user() {
    FILE *file = fopen("users.dat", "ab+"); 
    if (file == NULL) {
        printf("Error: Could not open database file!\n");
        return;
    }

    User new_user;
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    new_user.id = (file_size / sizeof(User)) + 1;
    new_user.is_active = 1;

    printf("Enter a username: ");
    scanf("%49s", new_user.username);

    fwrite(&new_user, sizeof(User), 1, file);
    printf("\nSuccess! User '%s' has been registered with ID %d.\n", new_user.username, new_user.id);

    fclose(file);
}

void view_users() {
    FILE *file = fopen("users.dat", "rb"); 
    if (file == NULL) {
        printf("\nNo users found. The database is empty or hasn't been created yet.\n");
        return;
    }

    User temp_user; 
    
    printf("\n--- Registered Users ---\n");
    printf("ID\tStatus\t\tUsername\n");
    printf("----------------------------------------\n");

    while (fread(&temp_user, sizeof(User), 1, file)) {
        printf("%d\t%s\t\t%s\n", 
               temp_user.id, 
               temp_user.is_active ? "Active" : "Inactive", 
               temp_user.username);
    }

    fclose(file);
}

void deregister_user() {
    FILE *file = fopen("users.dat", "rb+"); // Read and update mode
    if (file == NULL) {
        printf("\nError: Could not open database file! Make sure users exist first.\n");
        return;
    }

    int target_id;
    printf("Enter the ID of the user you want to deregister: ");
    scanf("%d", &target_id);

    User temp_user;
    
    // Calculate the exact byte offset of the target user in the file
    long offset = (target_id - 1) * sizeof(User);
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    // Check if the ID exists within the file's bounds
    if (offset >= 0 && offset < file_size) {
        fseek(file, offset, SEEK_SET); // Jump to the user's record
        fread(&temp_user, sizeof(User), 1, file);
        
        if (temp_user.is_active == 1) {
            temp_user.is_active = 0; // Toggle status
            fseek(file, offset, SEEK_SET); // Jump back to overwrite the record
            fwrite(&temp_user, sizeof(User), 1, file);
            printf("\nSuccess: User '%s' (ID: %d) has been deregistered.\n", temp_user.username, temp_user.id);
        } else {
            printf("\nNotice: User '%s' (ID: %d) is already inactive.\n", temp_user.username, target_id);
        }
    } else {
        printf("\nError: User with ID %d not found.\n", target_id);
    }

    fclose(file);
}