#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include "../include/network_clock.h"
#include "../include/time_setup.h"
#include "../include/config.h" // Include the header file for reading the port from the configuration file

#define MAX_BUFFER_SIZE 1024

void start_network_clock_client() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char server_reply[MAX_BUFFER_SIZE];

    int port = read_port_from_config();
    if (port == -1) {
        fprintf(stderr, "Failed to read the port from the configuration file.\n");
        return;
    }

    printf("Client: Port read from config file: %d\n", port); // Debug print

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return;
    }

    // Create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        fprintf(stderr, "Failed to create socket.\n");
        WSACleanup();
        return;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback address (localhost)
    server.sin_port = htons(port);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        fprintf(stderr, "Connection failed.\n");
        closesocket(client_socket);
        WSACleanup();
        return;
    }

    printf("Connected to server. Waiting for server response...\n");

    // Receive and display the server's response
    int bytes_received = recv(client_socket, server_reply, MAX_BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        server_reply[bytes_received] = '\0';
        printf("Server response: %s\n", server_reply);
    }

    // Close the socket and cleanup
    closesocket(client_socket);
    WSACleanup();
}

// int main() {
//     start_network_clock_client();
//     return 0;
// }
