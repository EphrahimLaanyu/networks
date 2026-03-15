// user.h
#ifndef USER_H
#define USER_H

// user structure
typedef struct {
    int id;
    char username[50];
    int is_active;
} User;


//message structure
typedef struct {
    int chat_id;
    int sender_id;
    int receiver_id;
    char message[256];
    char timestamp[30];
} Message;


/*
USER MANAGEMENT FUNCTIONS
*/

void register_user();
void view_users();
void deregister_user(); // <-- This is the missing line!

/*
MESSAGING FUNCTIONS
*/

void send_message();
void view_messages();

/* SEARCH FUNCTIONS */
void search_user_by_username();
void search_messages_by_keyword();


#endif