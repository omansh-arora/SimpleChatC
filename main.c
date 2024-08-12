
// Responsibility: Acts as the entry point for the application.
// It will parse command-line arguments (port numbers and machine names),
// initialize necessary data structures, and start the threads.

// Key Functions: Initialization, argument parsing, thread creation, etc..

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thread_manager.h"
#include "network.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <local_port> <remote_ip> <remote_port>\n", argv[0]);
        return 1;
    }

    int local_port = atoi(argv[1]);
    char *remote_ip = argv[2];
    int remote_port = atoi(argv[3]);

    setup_socket(local_port, remote_ip, remote_port);

    init_thread_manager();

    close_socket();
    return 0;
}