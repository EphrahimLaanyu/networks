// utils.c
#include <stdio.h>
#include <string.h>
#include "user.h"

int read_record(const char *filename, long index, void *out, size_t record_size) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) return 0;

    fseek(f, index * record_size, SEEK_SET);
    int result = fread(out, record_size, 1, f) == 1;
    fclose(f);
    return result;
}

int append_record(const char *filename, void *record, size_t record_size) {
    FILE *f = fopen(filename, "ab+");
    if (f == NULL) return -1;

    fseek(f, 0, SEEK_END);
    int new_id = (ftell(f) / record_size) + 1;

    fwrite(record, record_size, 1, f);
    fclose(f);
    return new_id;
}

int find_username(int user_id, char *out_username, size_t buf_size) {
    User temp;

    if (!read_record("users.dat", user_id - 1, &temp, sizeof(User))) {
        return 0;
    }

    if (temp.id != user_id) return 0;

    strncpy(out_username, temp.username, buf_size - 1);
    out_username[buf_size - 1] = '\0';
    return 1;
}

int get_next_id(const char *filename, size_t record_size) {
    FILE *f = fopen(filename, "ab+");
    if (f == NULL) return 1;

    fseek(f, 0, SEEK_END);
    int next_id = (ftell(f) / record_size) + 1;
    fclose(f);
    return next_id;
}

// Uses read_record for O(1) lookup instead of scanning
int user_exists(int id) {
    User temp;
    if (!read_record("users.dat", id - 1, &temp, sizeof(User))) {
        return 0;
    }
    return (temp.id == id && temp.is_active == 1);
}

// Looks up a message by chat_id using direct seek
int find_message(int chat_id, Message *out) {
    if (!read_record("messages.dat", chat_id - 1, out, sizeof(Message))) {
        return 0;
    }
    return (out->chat_id == chat_id);
}