// message.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "user.h"

// ─── shared helper ───────────────────────────────────────────────
// Fills a timestamp string. Declared static — only used inside message.c
static void fill_timestamp(char *buf, size_t buf_size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int year = t->tm_year + 1900;
    if (year < 0)    year = 0;
    if (year > 9999) year = 9999;

    snprintf(buf, buf_size,
             "%02d-%02d-%04d %02d:%02d:%02d",
             t->tm_mday, t->tm_mon + 1, year,
             t->tm_hour, t->tm_min, t->tm_sec);
}

// ─── shared helper ───────────────────────────────────────────────
// Prints a single formatted message record
static void print_message(Message *msg) {
    char sender_name[50], receiver_name[50];

    if (!find_username(msg->sender_id, sender_name, sizeof(sender_name)))
        strncpy(sender_name, "Unknown", sizeof(sender_name));
    if (!find_username(msg->receiver_id, receiver_name, sizeof(receiver_name)))
        strncpy(receiver_name, "Unknown", sizeof(receiver_name));

    printf("\nChat ID : %d\n", msg->chat_id);
    printf("From    : %s\n",   sender_name);
    printf("To      : %s\n",   receiver_name);

if (msg->reply_to_id > 0) {
    Message original;
    if (find_message(msg->reply_to_id, &original))
        printf("Replying to: %s", original.message);
    else
        printf("Reply to: Chat ID %d (not found)\n", msg->reply_to_id);
}

    printf("Message : %s",     msg->message);
    printf("Time    : %s\n",   msg->timestamp);
    printf("----------------------------\n");
}

// ─── send_message() ──────────────────────────────────────────────
void send_message() {
    Message msg;
    memset(&msg, 0, sizeof(Message));   // zero all fields — prevents garbage in any field

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
    getchar();
    fgets(msg.message, sizeof(msg.message), stdin);

    fill_timestamp(msg.timestamp, sizeof(msg.timestamp));

    // Stamp ID into struct before writing — not after
    msg.chat_id = get_next_id("messages.dat", sizeof(Message));

    if (append_record("messages.dat", &msg, sizeof(Message)) == -1) {
        printf("Error: Could not save message.\n");
        return;
    }

    printf("\nMessage sent! (Chat ID: %d)\n", msg.chat_id);
}

// ─── reply_to_message() ──────────────────────────────────────────
void reply_to_message() {
    Message reply;
    Message original;
    memset(&reply,    0, sizeof(Message));
    memset(&original, 0, sizeof(Message));

    printf("\n--- Reply to Message ---\n");

    printf("Enter your User ID (Sender): ");
    scanf("%d", &reply.sender_id);

    if (!user_exists(reply.sender_id)) {
        printf("Error: User does not exist or is inactive.\n");
        return;
    }



    printf("Enter the Chat ID you want to reply to: ");
    scanf("%d", &reply.reply_to_id);

    // Use find_message() from utils.c — direct seek by chat_id
    if (!find_message(reply.reply_to_id, &original)) {
        printf("Error: Message with Chat ID %d not found.\n", reply.reply_to_id);
        return;
    }

    // Show the original message for context
    printf("\n--- Original Message ---\n");
    print_message(&original);

    // The reply goes back to whoever sent the original
    reply.receiver_id = original.sender_id;

    // Guard: you can only reply to a message sent to you or by you
    if (original.receiver_id != reply.sender_id &&
        original.sender_id  != reply.sender_id) {
        printf("Error: You can only reply to messages in your own conversation.\n");
        return;
    }

    printf("Enter your reply: ");
    getchar();
    fgets(reply.message, sizeof(reply.message), stdin);

    fill_timestamp(reply.timestamp, sizeof(reply.timestamp));

    reply.chat_id = get_next_id("messages.dat", sizeof(Message));

    if (append_record("messages.dat", &reply, sizeof(Message)) == -1) {
        printf("Error: Could not save reply.\n");
        return;
    }

    printf("\nReply sent! (Chat ID: %d)\n", reply.chat_id);
}

// ─── view_messages() ─────────────────────────────────────────────
void view_messages() {
    int user_id;

    printf("\n--- View Messages ---\n");
    printf("Enter your User ID: ");
    scanf("%d", &user_id);

    if (!user_exists(user_id)) {
        printf("Error: User does not exist or is inactive.\n");
        return;
    }

    char my_name[50];
    if (!find_username(user_id, my_name, sizeof(my_name)))
        strncpy(my_name, "Unknown", sizeof(my_name));

    // ── SENT ──────────────────────────────────────────────────────
    FILE *file = fopen("messages.dat", "rb");
    if (file == NULL) {
        printf("\nNo messages found.\n");
        return;
    }

    int found = 0;
    Message msg;

    printf("\n[ Sent by %s ]\n", my_name);
    printf("=================================\n");

    while (fread(&msg, sizeof(Message), 1, file)) {
        if (msg.sender_id == user_id) {
            print_message(&msg);
            found = 1;
        }
    }

    if (!found)
        printf("No sent messages.\n");

    // ── RECEIVED ──────────────────────────────────────────────────
    rewind(file);   // scan the same file again from the top
    found = 0;

    printf("\n[ Received by %s ]\n", my_name);
    printf("=================================\n");

    while (fread(&msg, sizeof(Message), 1, file)) {
        if (msg.receiver_id == user_id) {
            print_message(&msg);
            found = 1;
        }
    }

    if (!found)
        printf("No received messages.\n");

    fclose(file);
}