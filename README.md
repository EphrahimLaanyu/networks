# One-on-One Chatting Application

A standalone **C program** that uses local binary files (`.dat`) as a database to handle user registration, one-on-one messaging with reply support, and user/message search.

The application runs entirely on **one computer** and does **not require internet, servers, or external services**.

---

## Project Structure

This project follows **Modular Programming** principles. Each file has a single, clearly defined responsibility.

| File            | Description                                                                                      |
| --------------- | ------------------------------------------------------------------------------------------------ |
| `main.c`        | Entry point. Presents the main menu and dispatches choices to the appropriate module.            |
| `user.h`        | Shared header containing the `User` and `Message` structs and all function prototypes.           |
| `register.c`    | Handles user registration, listing all users, and soft-deregistration.                          |
| `message.c`     | Handles sending messages, replying to messages, and viewing sent and received messages.          |
| `search.c`      | Handles partial username search and keyword-based message search.                               |
| `utils.c`       | Shared utility layer — generic file I/O functions reusable across modules.                      |
| `users.dat`     | Auto-generated binary file storing registered user records.                                     |
| `messages.dat`  | Auto-generated binary file storing sent messages and replies.                                   |

> ⚠️ **Do not open `.dat` files in a text editor.** They are stored in raw binary format and will appear as unreadable characters.

---

## Data Structures

Both structures are defined in `user.h` and shared across all modules.

### User
| Field       | Type       | Description                                                                 |
| ----------- | ---------- | --------------------------------------------------------------------------- |
| `id`        | `int`      | Unique identifier. Automatically assigned at registration.                  |
| `username`  | `char[50]` | The user's chosen display name. Maximum 49 characters.                      |
| `is_active` | `int`      | `1` = active, `0` = deregistered. Deregistration does not erase the record. |

### Message
| Field          | Type        | Description                                                                              |
| -------------- | ----------- | ---------------------------------------------------------------------------------------- |
| `chat_id`      | `int`       | Unique message identifier. Automatically assigned at send time.                          |
| `sender_id`    | `int`       | User ID of the sender. Must be an active registered user.                                |
| `receiver_id`  | `int`       | User ID of the receiver. Must be an active registered user.                              |
| `reply_to_id`  | `int`       | `0` for original messages. Set to the `chat_id` of the parent message for replies.      |
| `message`      | `char[256]` | The message content. Maximum 255 characters.                                             |
| `timestamp`    | `char[30]`  | Date and time the message was sent. Format: `DD-MM-YYYY HH:MM:SS`.                      |

---

## Features

### User Management
- Register a new user with a unique username
- View all registered users with their ID and status
- Deregister a user (soft-delete — the record is kept, the account is marked inactive)

### Messaging
- Send a message to any active registered user
- Reply to an existing message by Chat ID — the original message is shown for context
- View all messages sent **and** received by a given user

### Search
- Search for users by partial username match
- Search all messages by keyword

---

## Utility Layer (`utils.c`)

`utils.c` provides generic, struct-agnostic file functions shared across all modules.

| Function          | Description                                                                    |
| ----------------- | ------------------------------------------------------------------------------ |
| `read_record()`   | Reads one record at a given index from a binary file using a direct byte seek. |
| `append_record()` | Appends a record to a binary file and returns the new record's ID.             |
| `get_next_id()`   | Returns the next available ID for a file without writing.                      |
| `find_username()` | Resolves a user ID to a username string using `read_record()`.                 |
| `user_exists()`   | Returns `1` if a user ID exists and is active, `0` otherwise.                  |
| `find_message()`  | Retrieves a message record by Chat ID using a direct byte seek.                |

These functions accept a filename, a `void*` pointer, and a record size — they have no dependency on the `User` or `Message` structs directly, making them reusable in other applications.

---

## Data Storage

| File            | Contents                          |
| --------------- | --------------------------------- |
| `users.dat`     | Sequential `User` records         |
| `messages.dat`  | Sequential `Message` records      |

Files are created automatically the first time data is written. Records are fixed-size, so any record can be located by a direct offset calculation:

```
offset = (id - 1) * sizeof(StructType)
```

This gives O(1) lookup for user validation and message retrieval.

---

## How to Compile and Run

Because the project uses multiple `.c` files, all of them must be compiled together.

### Step 1 — Open the terminal

In VS Code, press:
```
Ctrl + `
```

### Step 2 — Navigate to the project folder

```bash
cd your-project-folder
```

### Step 3 — Compile

```bash
gcc main.c register.c message.c search.c utils.c -o chat
```

This produces an executable named `chat` (or `chat.exe` on Windows).

### Step 4 — Run

**Windows:**
```bash
.\chat.exe
```

**Linux / macOS:**
```bash
./chat
```

> ⚠️ If you change the `User` or `Message` struct (e.g. add a new field), delete `users.dat` and `messages.dat` before running again. The binary layout of existing records will not match the new struct size and will produce corrupted output.

---

## Adding New Modules

If you add a new `.c` file, include it in the compile command.

Example — adding a voting module:
```bash
gcc main.c register.c message.c search.c utils.c voting.c -o chat
```

The new module should `#include "user.h"` and declare any new functions in `user.h` under an appropriate section.

---

## Windows GCC Setup

If you see:
```
gcc is not recognized
```

GCC is not installed. Follow the steps below.

### Step 1 — Download MSYS2

Go to https://msys2.org and download `msys2-x86_64-latest.exe`. Run the installer with default settings.

### Step 2 — Install GCC

When the MSYS2 terminal opens, run:
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```
Type `Y` when prompted and wait for installation to complete.

### Step 3 — Add GCC to PATH

1. Open **Start Menu** and search for **Environment Variables**
2. Click **Edit the system environment variables**
3. Click **Environment Variables**
4. Under **User variables**, select `Path` and click **Edit**
5. Click **New** and add:
```
C:\msys64\ucrt64\bin
```
6. Click **OK** on all windows.

### Step 4 — Restart VS Code

Close and reopen VS Code completely for the PATH change to take effect.

### Step 5 — Verify

```bash
gcc --version
```

You should see version information printed, confirming GCC is ready.

---

## Menu Options

```
1. Register User
2. View Users
3. Deregister User
4. Send Message
5. Reply to Message
6. View Messages
7. Search Users
8. Search Messages
9. Exit
```