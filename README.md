# Standalone Chat & Voting Application

This is a standalone **C program** that uses local binary files (`.dat`) as a database to handle:

* User registration
* Messaging
* Voting

The application runs entirely on **one computer** and does **not require internet, servers, or external services**.

---

# 📁 Project Structure

This project follows **Modular Programming** principles.
Instead of placing everything inside one large file, the program is split into separate modules.

| File           | Description                                                                               |
| -------------- | ----------------------------------------------------------------------------------------- |
| `main.c`       | Main entry point of the program containing the user menu                                  |
| `user.h`       | Header file containing shared structures (`User` and `Message`) and function declarations |
| `register.c`   | Handles user registration and viewing stored users                                        |
| `message.c`    | Handles sending messages and displaying stored messages                                   |
| `users.dat`    | Auto-generated binary database storing user data                                          |
| `messages.dat` | Auto-generated binary database storing sent messages                                      |

⚠️ **Important:**
Do **not open `.dat` files in a a text editor**. They are stored in **raw binary format**, not readable text.

---

# 💬 Messaging System

The messaging module allows registered users to send messages to each other using their **user IDs**.

Each message includes the following information:

* **Chat ID** – a unique identifier automatically generated for every message
* **Sender ID** – the ID of the user sending the message
* **Receiver ID** – the ID of the user receiving the message
* **Message text** – the content of the message
* **Timestamp** – the exact date and time the message was sent

The system also verifies that the **sender and receiver exist and are active users** before allowing a message to be sent.

Messages can be viewed later through the program menu.where the user is prompted the sender id and the message sent by that user is displayed.

---

# 💾 Data Storage

The program stores information using **binary database files**.

| File           | Description                        |
| -------------- | ---------------------------------- |
| `users.dat`    | Stores registered user accounts    |
| `messages.dat` | Stores messages sent between users |

These files are automatically created the first time the program writes data.

Binary storage allows the program to **save and retrieve structured data efficiently**.

---

# 🚀 How to Compile and Run

Because the project contains **multiple C files**, you must compile them together using the terminal.

### Step 1: Open the VS Code Terminal

Press:

```
Ctrl + `
```

---

### Step 2: Make Sure You Are in the Project Folder

Example:

```bash
cd your-project-folder
```

---

### Step 3: Compile the Program

Run:

```bash
gcc main.c register.c message.c -o app
```

This creates an executable file named:

```
app.exe
```

---

### Step 4: Run the Program

```bash
.\app.exe
```

---

# ➕ Adding New Modules

If you create a new module file, you must include it when compiling.

Example: **search or  voting**

```bash
gcc main.c register.c message.c search.c -o app
```

---

# 🛠️ Windows C Compiler Setup Guide

If you see an error like:

```
gcc is not recognized
```

it means **GCC is not installed on your system**.

Follow the steps below.

---

# Step 1: Download MSYS2

Go to the official website:

https://msys2.org

Download:

```
msys2-x86_64-latest.exe
```

Run the installer and click **Next** through the default installation steps.

---

# Step 2: Install GCC

After installation, the **MSYS2 terminal** will open automatically.

Paste the following command:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

When prompted:

```
Proceed with installation? [Y/n]
```

Type:

```
Y
```

Then press **Enter**.

Wait for the installation to finish.

---

# Step 3: Add GCC to Windows PATH

This step allows **Windows and VS Code to find the compiler**.

1. Open the **Start Menu**
2. Search for **Environment Variables**
3. Click **Edit the system environment variables**
4. Click **Environment Variables**
5. In the **User variables** section, find `Path`
6. Click **Edit**
7. Click **New**
8. Add the following path:

```
C:\msys64\ucrt64\bin
```

9. Click **OK** on all windows to save changes.

---

# Step 4: Restart VS Code

Close **VS Code completely** and reopen it.

This step is **required** for the PATH update to take effect.

---

# Step 5: Verify GCC Installation

Open the VS Code terminal and run:

```bash
gcc --version
```

If the installation was successful, you will see the GCC version information.

Example:

```
gcc (Rev...) 13.x.x
Copyright (C) Free Software Foundation
```

---

# ✅ Ready to Develop

You can now:

* Compile C programs
* Build modular projects
* Work with binary databases
* Extend the chat and voting system

Example compile command:

```bash
gcc main.c register.c message.c -o app
```

Run:

```bash
.\app.exe
```
