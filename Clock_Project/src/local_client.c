// #include <stdio.h>
// #include <stdlib.h>
// #include <winsock2.h>

// #define MAX_BUFFER_SIZE 1024 // <-----------------------------------------

// int main() {
//     WSADATA wsa;
//     SOCKET client_socket;
//     struct sockaddr_in server;
//     int port = 12345; // <-----------------------------------------
//     char server_reply[MAX_BUFFER_SIZE];
//     char user_input[MAX_BUFFER_SIZE];

//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//         fprintf(stderr, "Failed to initialize Winsock.\n");
//         return 1;
//     }

//     if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//         fprintf(stderr, "Failed to create socket.\n");
//         WSACleanup();
//         return 1;
//     }

//     server.sin_family = AF_INET;
//     server.sin_addr.s_addr = inet_addr("127.0.0.1");// <-----------------------------------------
//     server.sin_port = htons(port);

//     if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
//         fprintf(stderr, "Connection failed.\n");
//         closesocket(client_socket);
//         WSACleanup();
//         return 1;
//     }

//     printf("Connected to the server.\n");

//     while (1) { // Loop to handle multiple requests
//         if (recv(client_socket, server_reply, MAX_BUFFER_SIZE, 0) > 0) {
//             printf("Server message: %s\n", server_reply);

//             // Read user input
//             fgets(user_input, MAX_BUFFER_SIZE, stdin);
//             user_input[strlen(user_input) - 1] = '\0';  // Replace the newline character with null character

//             // Send user input to server
//             send(client_socket, user_input, strlen(user_input), 0);

//             if (strcmp(user_input, "3") == 0) { // If user chose to exit
//                 break;
//             }
//         }
//     }

//     closesocket(client_socket);
//     WSACleanup();
//     return 0;
// }
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
    char user_input[MAX_BUFFER_SIZE];

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

    while (1) { 
        if (recv(client_socket, server_reply, MAX_BUFFER_SIZE, 0) > 0) {
            printf("Server message: %s\n", server_reply);

            fgets(user_input, MAX_BUFFER_SIZE, stdin);
            user_input[strlen(user_input) - 1] = '\0'; 

            send(client_socket, user_input, strlen(user_input), 0);

            if (strcmp(user_input, "4") == 0) { // If user chose to exit
                break;
            }
        }
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
