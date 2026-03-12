// message.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "user.h"

/*FUNCTION: user_exists()*/
int user_exists(int id) {

    FILE *file = fopen("users.dat", "rb");

    if (file == NULL) {
        return 0;
    }

    User temp;

    while (fread(&temp, sizeof(User), 1, file)) {

        if (temp.id == id && temp.is_active == 1) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}



/* FUNCTION: send_message() Allows one registered user to send a message to another.*/
void send_message() {

    FILE *file;
    Message msg;

    printf("\n--- Send Message ---\n");

    printf("Enter Sender ID: ");
    scanf("%d", &msg.sender_id);

    if (!user_exists(msg.sender_id)) {
        printf("Error: Sender does not exist or is inactive.\n");
        return;
    }

    printf("Enter Receiver ID: ");
    scanf("%d", &msg.receiver_id);

    if (!user_exists(msg.receiver_id)) {
        printf("Error: Receiver does not exist or is inactive.\n");
        return;
    }

    printf("Enter message: ");
    getchar(); // clear buffer
    fgets(msg.message, sizeof(msg.message), stdin);


    /*Open messages database*/

    file = fopen("messages.dat", "ab+");

    if (file == NULL) {
        printf("Error: Could not open message database.\n");
        return;
    }


    /*Generate Chat ID*/

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    msg.chat_id = (file_size / sizeof(Message)) + 1;


    /*Generate Timestamp*/

    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);

    sprintf(msg.timestamp,
            "%02d-%02d-%04d %02d:%02d:%02d",
            time_info->tm_mday,
            time_info->tm_mon + 1,
            time_info->tm_year + 1900,
            time_info->tm_hour,
            time_info->tm_min,
            time_info->tm_sec);


    /* Save message to file*/

    fwrite(&msg, sizeof(Message), 1, file);

    printf("\nMessage sent successfully!\n");

    fclose(file);
}



/*
FUNCTION: view_messages() Displays all stored messages from messages.dat
*/

void view_messages() {

    FILE *file = fopen("messages.dat", "rb");

    if (file == NULL) {
        printf("\nNo messages found.\n");
        return;
    }

    int sender_id;
    int found = 0;
    Message msg;

    printf("\n--- View Messages by Sender ---\n");
    printf("Enter Sender ID: ");
    scanf("%d", &sender_id);

    // Optional: verify sender exists
    if (!user_exists(sender_id)) {
        printf("Error: Sender does not exist or is inactive.\n");
        fclose(file);
        return;
    }

    printf("\nMessages sent by User ID %d:\n", sender_id);
    printf("---------------------------------\n");

    while (fread(&msg, sizeof(Message), 1, file)) {

        if (msg.sender_id == sender_id) {

            printf("\nChat ID: %d\n", msg.chat_id);
            printf("Receiver ID: %d\n", msg.receiver_id);
            printf("Message: %s", msg.message);
            printf("Timestamp: %s\n", msg.timestamp);
            printf("----------------------------\n");

            found = 1;
        }
    }

    if (!found) {
        printf("No messages found from this sender.\n");
    }

    fclose(file);
}