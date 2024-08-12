### Overview

This project is a simple "chat"-like facility named SimpleChat that enables communication between two users on different terminals (or Xterms). The main goal of the project is to learn and implement various concepts related to Inter-Process Communication (IPC), concurrency, and multi-threaded programming using POSIX threads (`pthreads`). The project also incorporates the use of UNIX UDP sockets for network communication.

### Features

- **UNIX UDP IPC**: Communication between two processes on different machines using UDP sockets.
- **Concurrency with pthreads**: Multi-threaded programming to handle input, output, and network communication.
- **Client/Server Model**: Implementation of a client/server model where each user can both send and receive messages.
- **Critical Section Handling**: Proper synchronization using mutexes and condition variables to handle shared resources between threads.

### Required Components

The SimpleChat application consists of four main threads:

1. **Keyboard Input Thread**: Captures input from the user's keyboard and adds it to the list of messages to be sent.
2. **UDP Output Thread**: Sends messages from the list to the remote user via UDP.
3. **UDP Input Thread**: Receives messages from the remote user and adds them to the list of messages to be printed.
4. **Screen Output Thread**: Prints messages from the list to the local terminal screen.

### Usage

To initiate an SimpleChat session, both users must agree on the machine names and port numbers they will use. 

