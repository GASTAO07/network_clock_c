// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <winsock2.h>
// #include "../include/network_clock.h"

// #define MAX_BUFFER_SIZE 1024

// // Function to handle server response
// void handle_server_response(SOCKET client_socket) {
//     char buffer[MAX_BUFFER_SIZE];
//     int bytes_received;

//     // Receive data from the server
//     bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
//     if (bytes_received > 0) {
//         buffer[bytes_received] = '\0';
//         printf("Received from server: %s\n", buffer);
//     }
// }

// void start_network_clock_client() {
//     WSADATA wsa;
//     SOCKET client_socket;
//     struct sockaddr_in server;
//     char *server_ip = "127.0.0.1"; // Change this to the IP of the server
//     int port = 12345;

//     // Initialize Winsock
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//         fprintf(stderr, "Failed to initialize Winsock.\n");
//         return;
//     }

//     // Create a socket
//     if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//         fprintf(stderr, "Failed to create socket.\n");
//         WSACleanup();
//         return;
//     }

//     // Prepare the sockaddr_in structure
//     server.sin_family = AF_INET;
//     server.sin_addr.s_addr = inet_addr(server_ip);
//     server.sin_port = htons(port);

//     // Connect to the server
//     if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
//         fprintf(stderr, "Connection failed.\n");
//         closesocket(client_socket);
//         WSACleanup();
//         return;
//     }

//     // Request time from the server
//     char *request = "Time request";
//     if (send(client_socket, request, strlen(request), 0) < 0) {
//         fprintf(stderr, "Failed to send request to the server.\n");
//         closesocket(client_socket);
//         WSACleanup();
//         return;
//     }

//     // Handle server response
//     handle_server_response(client_socket);

//     // Cleanup and close the socket
//     closesocket(client_socket);
//     WSACleanup();
// }

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <winsock2.h>
// #include "../include/network_clock.h"
// #include "../include/time_setup.h"
// #include "../include/config.h" // Include the header file for reading the port from the configuration file

// #define MAX_BUFFER_SIZE 1024

// void start_network_clock_client() {
//     WSADATA wsa;
//     SOCKET client_socket;
//     struct sockaddr_in server;
//     char server_reply[MAX_BUFFER_SIZE];

//     int port = read_port_from_config();
//     if (port == -1) {
//         fprintf(stderr, "Failed to read the port from the configuration file.\n");
//         return;
//     }

//     printf("Client: Port read from config file: %d\n", port); // Debug print

//     // Initialize Winsock
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//         fprintf(stderr, "Failed to initialize Winsock.\n");
//         return;
//     }

//     // Create a socket
//     if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//         fprintf(stderr, "Failed to create socket.\n");
//         WSACleanup();
//         return;
//     }

//     // Prepare the sockaddr_in structure
//     server.sin_family = AF_INET;
//     server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback address (localhost)
//     server.sin_port = htons(port);

//     // Connect to the server
//     if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
//         fprintf(stderr, "Connection failed.\n");
//         closesocket(client_socket);
//         WSACleanup();
//         return;
//     }

//     printf("Connected to server. Waiting for server response...\n");

//     // Receive and display the server's response
//     int bytes_received = recv(client_socket, server_reply, MAX_BUFFER_SIZE, 0);
//     if (bytes_received > 0) {
//         server_reply[bytes_received] = '\0';
//         printf("Server response: %s\n", server_reply);
//     }

//     // Close the socket and cleanup
//     closesocket(client_socket);
//     WSACleanup();
// }

// int main() {
//     start_network_clock_client();
//     return 0;
// }
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
