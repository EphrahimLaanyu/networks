// user.h
#ifndef USER_H
#define USER_H

// user structure
typedef struct {
    int id;
    char username[50];
    int is_active;
} User;

// message structure
typedef struct {
    int chat_id;
    int sender_id;
    int receiver_id;
    int reply_to_id;
    char message[256];
    char timestamp[30];
} Message;

/* USER MANAGEMENT FUNCTIONS */
void register_user();
void view_users();
void deregister_user();

/* MESSAGING FUNCTIONS */
void send_message();
void view_messages();
void reply_to_message();

/* SEARCH FUNCTIONS */
void search_user_by_username();
void search_messages_by_keyword();

/* UTILITY FUNCTIONS */
int read_record(const char *filename, long index, void *out, size_t record_size);
int append_record(const char *filename, void *record, size_t record_size);
int find_username(int user_id, char *out_username, size_t buf_size);
int get_next_id(const char *filename, size_t record_size);
int user_exists(int id);
int find_message(int chat_id, Message *out);

#endif