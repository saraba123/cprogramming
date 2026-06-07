#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 62555

int main() {
    int client_fd = -1;
    struct sockaddr_in server_addr, client_addr;
    char buffer[256] = {0};

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        fprintf(stderr, "socket creation failed\n");
        exit(0);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    if((inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr)) < 0) {
        fprintf(stderr, "Invalid IPaddress %s\n", SERVER_IP);
        exit(0);
    }
    socklen_t server_len = sizeof(server_addr);
    //connect to server
    if(connect(client_fd, (const struct sockaddr*)&server_addr, server_len) < 0) {
        fprintf(stderr, "Failed to connect\n");
        exit(0);
    }

    const char *sendmsg = "Hello! Server";
    //sent msg to server
    if(send(client_fd, sendmsg, strlen(sendmsg), 0) < 0) {
        fprintf(stderr, "Failed to send the msg\n");
        exit(0);
    }

    // receiver msg from server
    ssize_t recvlen = recv(client_fd, buffer, sizeof(buffer), 0);
    if(recvlen < 0) {
        fprintf(stderr, "Failed to recv the buffer\n");
        exit(0);
    }
    buffer[recvlen +1] = '\0';

    fprintf(stderr, "Received message from server: %s\n", buffer);
    close(client_fd);
    return 0;
}

# gcc simpleTCPClient.c -o client 
# ./client
# Received message from server: Thanks for your message!!
#
#
#
