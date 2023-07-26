#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include "../include/network_clock.h"

#define MAX_BUFFER_SIZE 1024

// Function to handle client requests
void handle_client(SOCKET client_socket) {
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;

    // Get current date and time
    time_t current_time;
    time(&current_time);
    char *date_time = ctime(&current_time);

    // Send date and time to the client
    send(client_socket, date_time, strlen(date_time), 0);

    // Receive data from the client
    bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received from client: %s\n", buffer);
    }

    closesocket(client_socket);
}

void start_network_clock_server() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int port = 12345;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return;
    }

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        fprintf(stderr, "Failed to create socket.\n");
        WSACleanup();
        return;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return;
    }

    // Listen for incoming connections
    listen(server_socket, 3);

    printf("Server listening on port %d...\n", port);

    // Accept and handle incoming connections
    int c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        // Handle client request
        handle_client(client_socket);
    }

    if (client_socket == INVALID_SOCKET) {
        fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return;
    }

    // Cleanup and close the socket
    closesocket(server_socket);
    WSACleanup();
}