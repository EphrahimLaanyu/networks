#include <stdio.h>
#include <string.h>
#include "user.h"

void trim_newline(char *str)
{
	str[strcspn(str, "\n")] = 0;
}

void search_user_by_username()
{
	FILE *file = fopen("users.dat", "rb");
	if (file == NULL)
	{
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

	while (fread(&temp, sizeof(User), 1, file))
	{
		if (strstr(temp.username, term) != NULL)
		{
			printf("%-5d | %-20s | %-10s\n",
						 temp.id,
						 temp.username,
						 temp.is_active ? "Active" : "Inactive");
			found = 1;
		}
	}

	if (!found)
	{
		printf("No users found matching '%s'.\n", term);
	}

	fclose(file);
}

void search_messages_by_keyword()
{
	FILE *file = fopen("messages.dat", "rb");
	if (file == NULL)
	{
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
	while (fread(&msg, sizeof(Message), 1, file))
	{
		if (strstr(msg.message, keyword) != NULL)
		{

			char sender_name[50], receiver_name[50];
			if (!find_username(msg.sender_id, sender_name, sizeof(sender_name)))
				strncpy(sender_name, "Unknown", sizeof(sender_name));
			if (!find_username(msg.receiver_id, receiver_name, sizeof(receiver_name)))
				strncpy(receiver_name, "Unknown", sizeof(receiver_name));

			printf("\n[%s]\n", msg.timestamp);
			printf("From: %s -> To: %s\n", sender_name, receiver_name);
			printf("Message: %s\n", msg.message);
			printf("----------------------------\n");
			found = 1;
		}
	}

	if (!found)
	{
		printf("No messages containing '%s' were found.\n", keyword);
	}

	fclose(file);
}