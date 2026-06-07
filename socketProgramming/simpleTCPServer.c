#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 62555

int main()
{
    int server_fd = -1, client_fd = -1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[256] = {0};
    int opt = 1;

    //Creating TCP server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        fprintf(stderr,  "TCP Socket creation is failed\n");
        exit(0);
    }

    //Prepare IP and Port details to bind
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_family = AF_INET;

    if(inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) < 0) {
        fprintf(stderr,  "inet_pton is failed\n");
        exit(0);
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        fprintf(stderr,  "Failed to set Reuse address\n");
    }

    if(bind(server_fd, (const struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr,  "Failed to bind the server\n");
        exit(0);
    }

    //Inform the kernel to manage the TCP handshake, wait queue maximum length is 5
    if(listen(server_fd, 5) < 0) {
        fprintf(stderr,  "Failed to update the listen\n");
        exit(0);
    }

    fprintf(stderr, "Server listening on %d port:\n", SERVER_PORT);
    //Accept the incoming request.
    if((client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_len)) < 0)
    {
        fprintf(stderr,  "Accept error\n");
        exit(0);
    }
    fprintf(stderr, "Receiving the request from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    //Read the message from client
    ssize_t recv_len = recv(client_fd, buffer, sizeof(buffer), 0);
    if(recv_len < 0) {
        fprintf(stderr, "Received error\n");
        exit(0);
    }

    buffer[recv_len + 1] = '\0';
    fprintf(stderr, "Received message: %s\n", buffer);
 
    const char *sendmsg = "Thanks for your message!!";
    if(send(client_fd, sendmsg, strlen(sendmsg), 0) < 0) {
        printf("Failed to send the message back\n");
        exit(0);
    }

    close(server_fd);
    close(client_fd);
    return 0;
}

# gcc simpleTCPServer.c -o server
# ./server
# Server listening on 62555 port:
# Receiving the request from 127.0.0.1:60614
# Received message: Hello! Server
#
