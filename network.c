
// Responsibility: Handles all network-related operations,
// including setting up UDP sockets, sending messages,
// and receiving messages.

// Key Functions: setup socket, send message, receive message, etc..

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int sockfd;
char *remote_ip;
int remote_port;

int setup_socket(int local_port, char *hostname, int port)
{
    struct sockaddr_in local_addr;
    struct addrinfo hints, *result;

    remote_ip = NULL;
    remote_port = port;

    // Create the socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Failed to create socket");
        return -1;
    }

    // Zero out the structure
    memset(&local_addr, 0, sizeof(local_addr));

    local_addr.sin_family = AF_INET;                // IPv4
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Any incoming interface
    local_addr.sin_port = htons(local_port);        // Local port to listen on

    // Bind the socket to the local port
    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        return -1;
    }

    if (sockfd < 0)
    {
        perror("Error setting up the socket\n");
        return 1;
    }

    // Resolve the hostname
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_DGRAM;

    int res = getaddrinfo(hostname, NULL, &hints, &result);
    if (res != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return -1;
    }

    struct sockaddr_in *addr = (struct sockaddr_in *)result->ai_addr;
    remote_ip = inet_ntoa(addr->sin_addr);

    freeaddrinfo(result);

    return sockfd;
}

int send_message(const char *message)
{
    struct sockaddr_in remote_addr;

    // Zero out the structure
    memset(&remote_addr, 0, sizeof(remote_addr));

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remote_port);

    // Convert IPv4 or IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, remote_ip, &remote_addr.sin_addr) <= 0)
    {
        perror("inet_pton failed");
        return -1;
    }

    // Send the message
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0)
    {
        perror("sendto failed");
        return -1;
    }

    return 0;
}

int receive_message(char *buffer, int buffer_length)
{
    struct sockaddr_in remote_addr;
    socklen_t addr_len = sizeof(remote_addr);

    // Zero out the buffer
    memset(buffer, 0, buffer_length);

    // Receive a message
    int len = recvfrom(sockfd, buffer, buffer_length, 0, (struct sockaddr *)&remote_addr, &addr_len);
    if (len < 0)
    {
        perror("recvfrom failed");
        return -1;
    }

    return len; // Return the length of the received message
}

void close_socket()
{
    close(sockfd);
}
