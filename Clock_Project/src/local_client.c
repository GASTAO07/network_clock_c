#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define MAX_BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    int port = 12345;
    char server_reply[MAX_BUFFER_SIZE];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return 1;
    }

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        fprintf(stderr, "Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        fprintf(stderr, "Connection failed.\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("Connected to the server.\n");

    if (recv(client_socket, server_reply, MAX_BUFFER_SIZE, 0) > 0) {
        printf("Server message: %s\n", server_reply);
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
