// user.h
#ifndef USER_H
#define USER_H

// Define the struct here so ALL files can see it
typedef struct {
    int id;
    char username[50];
    int is_active;
} User;

// Declare the functions that exist in register.c
void register_user();
void view_users();

#endif