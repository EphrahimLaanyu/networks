// user.h
#ifndef USER_H
#define USER_H

/*
-------------------------------------------------------
USER STRUCTURE
-------------------------------------------------------
This structure represents a registered user in the system.

Fields:
id         -> Unique ID assigned automatically during registration
username   -> The user's chosen name (max 49 characters + null terminator)
is_active  -> Indicates if the user is active (1) or deregistered (0)
*/

typedef struct {
    int id;
    char username[50];
    int is_active;
} User;


/*
-------------------------------------------------------
MESSAGE STRUCTURE
-------------------------------------------------------
This structure represents a message sent between users.

Fields:
chat_id      -> Unique ID for each message
sender_id    -> ID of the user sending the message
receiver_id  -> ID of the user receiving the message
message      -> The actual message text
timestamp    -> Date and time the message was sent
*/

typedef struct {
    int chat_id;
    int sender_id;
    int receiver_id;
    char message[256];
    char timestamp[30];
} Message;


/*
-------------------------------------------------------
USER MANAGEMENT FUNCTIONS
-------------------------------------------------------
These functions are implemented in register.c
*/

void register_user();
void view_users();


/*
-------------------------------------------------------
MESSAGING FUNCTIONS
-------------------------------------------------------
These functions will be implemented in message.c
*/

void send_message();
void view_messages();


#endif