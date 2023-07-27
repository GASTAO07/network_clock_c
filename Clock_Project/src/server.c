// // // // #include <stdio.h>
// // // // #include <string.h>
// // // // #include <stdlib.h>
// // // // #include <time.h>
// // // // #include <winsock2.h>
// // // // #include "../include/network_clock.h"
// // // // #include "../include/time_setup.h"
// // // // #include "../include/config.h"

// // // // #define MAX_BUFFER_SIZE 1024

// // // // // Function to handle client requests
// // // // void handle_client(SOCKET client_socket) {
// // // //     char buffer[MAX_BUFFER_SIZE];
// // // //     int bytes_received;

// // // //     // Get current date and time
// // // //     time_t current_time;
// // // //     time(&current_time);
// // // //     char *date_time = ctime(&current_time);

// // // //     // Send date and time to the client
// // // //     send(client_socket, date_time, strlen(date_time), 0);

// // // //     // Receive data from the client
// // // //     bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// // // //     if (bytes_received > 0) {
// // // //         buffer[bytes_received] = '\0';
// // // //         printf("Received from client: %s\n", buffer);
// // // //     }

// // // //     closesocket(client_socket);
// // // // }

// // // // void start_network_clock_server() {
// // // //     WSADATA wsa;
// // // //     SOCKET server_socket, client_socket;
// // // //     struct sockaddr_in server, client;
// // // //     int port = 12345;

// // // //     // Initialize Winsock
// // // //     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
// // // //         fprintf(stderr, "Failed to initialize Winsock.\n");
// // // //         return;
// // // //     }

// // // //     // Create a socket
// // // //     if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
// // // //         fprintf(stderr, "Failed to create socket.\n");
// // // //         WSACleanup();
// // // //         return;
// // // //     }

// // // //     // Prepare the sockaddr_in structure
// // // //     server.sin_family = AF_INET;
// // // //     server.sin_addr.s_addr = INADDR_ANY;
// // // //     server.sin_port = htons(port);

// // // //     // Bind the socket
// // // //     if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
// // // //         fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
// // // //         closesocket(server_socket);
// // // //         WSACleanup();
// // // //         return;
// // // //     }

// // // //     // Listen for incoming connections
// // // //     listen(server_socket, 3);

// // // //     printf("Server listening on port %d...\n", port);

// // // //     // Accept and handle incoming connections
// // // //     int c = sizeof(struct sockaddr_in);
// // // //     while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
// // // //         printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

// // // //         // Handle client request
// // // //         handle_client(client_socket);
// // // //     }

// // // //     if (client_socket == INVALID_SOCKET) {
// // // //         fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
// // // //         closesocket(server_socket);
// // // //         WSACleanup();
// // // //         return;
// // // //     }

// // // //     // Cleanup and close the socket
// // // //     closesocket(server_socket);
// // // //     WSACleanup();
// // // // }

// // // #include <stdio.h>
// // // #include <string.h>
// // // #include <stdlib.h>
// // // #include <winsock2.h>
// // // #include "../include/network_clock.h"
// // // #include "../include/time_setup.h"
// // // #include "../include/config.h" // Include the header file to access read_port_from_config function

// // // #define MAX_BUFFER_SIZE 1024

// // // // Function to handle client requests
// // // void handle_client(SOCKET client_socket) {
// // //     char buffer[MAX_BUFFER_SIZE];
// // //     int bytes_received;

// // //     // Get current date and time using the Windows API
// // //     SYSTEMTIME current_time;
// // //     GetSystemTime(&current_time);

// // //     // Convert time to string format
// // //     sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
// // //             current_time.wYear,
// // //             current_time.wMonth,
// // //             current_time.wDay,
// // //             current_time.wHour,
// // //             current_time.wMinute,
// // //             current_time.wSecond);

// // //     // Send date and time to the client
// // //     send(client_socket, buffer, strlen(buffer), 0);

// // //     // Receive data from the client
// // //     bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// // //     if (bytes_received > 0) {
// // //         buffer[bytes_received] = '\0';
// // //         printf("Received from client: %s\n", buffer);
// // //     }

// // //     closesocket(client_socket);
// // // }

// // // void start_network_clock_server() {
// // //     WSADATA wsa;
// // //     SOCKET server_socket, client_socket;
// // //     struct sockaddr_in server, client;
// // //     int port = read_port_from_config();
// // //     if (port == -1) {
// // //         fprintf(stderr, "Failed to read the port from the configuration file.\n");
// // //         return;
// // //     }

// // //     // Initialize Winsock
// // //     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
// // //         fprintf(stderr, "Failed to initialize Winsock.\n");
// // //         return;
// // //     }

// // //     // Create a socket
// // //     if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
// // //         fprintf(stderr, "Failed to create socket.\n");
// // //         WSACleanup();
// // //         return;
// // //     }

// // //     // Prepare the sockaddr_in structure
// // //     server.sin_family = AF_INET;
// // //     server.sin_addr.s_addr = INADDR_ANY;
// // //     server.sin_port = htons(port);

// // //     // Bind the socket
// // //     if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
// // //         fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
// // //         closesocket(server_socket);
// // //         WSACleanup();
// // //         return;
// // //     }

// // //     // Listen for incoming connections
// // //     listen(server_socket, 3);

// // //     printf("Server listening on port %d...\n", port);

// // //     // Accept and handle incoming connections
// // //     int c = sizeof(struct sockaddr_in);
// // //     while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
// // //         printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

// // //         // Handle client request
// // //         handle_client(client_socket);
// // //     }

// // //     if (client_socket == INVALID_SOCKET) {
// // //         fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
// // //         closesocket(server_socket);
// // //         WSACleanup();
// // //         return;
// // //     }

// // //     // Cleanup and close the socket
// // //     closesocket(server_socket);
// // //     WSACleanup();
// // // }

// // // // #include <stdio.h>
// // // // #include <winsock2.h>
// // // // #include "../include/network_clock.h"
// // // // #include "../include/config.h"

// // // // int main() {
// // // //     // Start the network clock server
// // // //     start_network_clock_server();
// // // //     return 0;
// // // // }

// // #include <stdio.h>
// // #include <string.h>
// // #include <stdlib.h>
// // #include <winsock2.h>
// // #include "../include/network_clock.h"
// // #include "../include/time_setup.h"
// // #include "../include/config.h" // Include the header file to access read_port_from_config function
// // #include "../include/time_setup.h" // Include the header file to access read_port_from_config function

// // #define MAX_BUFFER_SIZE 1024

// // void handle_client(SOCKET client_socket) {
// //     char buffer[MAX_BUFFER_SIZE];
// //     int bytes_received;

// //     // Get current date and time using the Windows API
// //     SYSTEMTIME current_time;
// //     GetSystemTime(&current_time);

// //     // Convert time to string format
// //     sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
// //             current_time.wYear,
// //             current_time.wMonth,
// //             current_time.wDay,
// //             current_time.wHour,
// //             current_time.wMinute,
// //             current_time.wSecond);

// //     // Send date and time to the client
// //     send(client_socket, buffer, strlen(buffer), 0);

// //     // Receive data from the client
// //     bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// //     if (bytes_received > 0) {
// //         buffer[bytes_received] = '\0';

// //         // Check the client's choice
// //         int choice = atoi(buffer);
// //         switch (choice) {
// //             case 1:
// //                 // Help: Print available options
// //                 send(client_socket, "Available options:\n[1] Help\n[2] Get the current system date and time\n[3] Set a new date and time\n[0] Exit\n", strlen(buffer), 0);
// //                 break;

// //             case 2:
// //                 // Get the current system date and time
// //                 printCurrentSystemDateTime();
// //                 break;

// //             case 3:
// //                 // Set a new date and time
// //                 send(client_socket, "Enter the new date and time in the format: YYYY-MM-DD HH:MM:SS\n", strlen(buffer), 0);
// //                 bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// //                 if (bytes_received > 0) {
// //                     buffer[bytes_received] = '\0';
// //                     int year, month, day, hour, minute, second;
// //                     sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
// //                     setSystemDateTime(year, month, day, hour, minute, second);
// //                 }
// //                 break;

// //             case 0:
// //                 // Exit
// //                 send(client_socket, "Goodbye!\n", strlen(buffer), 0);
// //                 break;

// //             default:
// //                 // Invalid choice
// //                 send(client_socket, "Invalid choice. Enter a valid option.\n", strlen(buffer), 0);
// //                 break;
// //         }
// //     }

// //     closesocket(client_socket);
// // }

// // // // Function to handle client requests
// // // void handle_client(SOCKET client_socket) {
// // //     char buffer[MAX_BUFFER_SIZE];
// // //     int bytes_received;

// // //     // Get current date and time using the Windows API
// // //     SYSTEMTIME current_time;
// // //     GetSystemTime(&current_time);

// // //     // Convert time to string format
// // //     sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
// // //             current_time.wYear,
// // //             current_time.wMonth,
// // //             current_time.wDay,
// // //             current_time.wHour,
// // //             current_time.wMinute,
// // //             current_time.wSecond);

// // //     // Send date and time to the client
// // //     send(client_socket, buffer, strlen(buffer), 0);

// // //     // Receive data from the client
// // //     bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// // //     if (bytes_received > 0) {
// // //         buffer[bytes_received] = '\0';
// // //         printf("Received from client: %s\n", buffer);
// // //     }

// // //     closesocket(client_socket);
// // // }

// // void start_network_clock_server() {
// //     WSADATA wsa;
// //     SOCKET server_socket, client_socket;
// //     struct sockaddr_in server, client;
// //     int port = read_port_from_config();
// //     if (port == -1) {
// //         fprintf(stderr, "Failed to read the port from the configuration file.\n");
// //         return;
// //     }

// //     // Initialize Winsock
// //     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
// //         fprintf(stderr, "Failed to initialize Winsock.\n");
// //         return;
// //     }

// //     // Create a socket
// //     if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
// //         fprintf(stderr, "Failed to create socket.\n");
// //         WSACleanup();
// //         return;
// //     }

// //     // Prepare the sockaddr_in structure
// //     server.sin_family = AF_INET;
// //     server.sin_addr.s_addr = INADDR_ANY;
// //     server.sin_port = htons(port);

// //     // Bind the socket
// //     if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
// //         fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
// //         closesocket(server_socket);
// //         WSACleanup();
// //         return;
// //     }

// //     // Listen for incoming connections
// //     listen(server_socket, 3);

// //     printf("Server listening on port %d...\n", port);

// //     // Accept and handle incoming connections
// //     int c = sizeof(struct sockaddr_in);
// //     while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
// //         printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

// //         // Handle client request
// //         handle_client(client_socket);
// //     }

// //     if (client_socket == INVALID_SOCKET) {
// //         fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
// //         closesocket(server_socket);
// //         WSACleanup();
// //         return;
// //     }

// //     // Cleanup and close the socket
// //     closesocket(server_socket);
// //     WSACleanup();
// // }

// // int main() {
// //     start_network_clock_server();
// //     return 0;
// // }

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <winsock2.h>
// #include "../include/network_clock.h"
// #include "../include/time_setup.h"
// #include "../include/config.h"

// #define MAX_BUFFER_SIZE 1024

// void handle_client(SOCKET client_socket) {
//     char buffer[MAX_BUFFER_SIZE];
//     int bytes_received;

//     // Get current date and time using the Windows API
//     SYSTEMTIME current_time;
//     GetSystemTime(&current_time);

//     // Convert time to string format
//     sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
//             current_time.wYear,
//             current_time.wMonth,
//             current_time.wDay,
//             current_time.wHour,
//             current_time.wMinute,
//             current_time.wSecond);

//     // Send date and time to the client
//     send(client_socket, buffer, strlen(buffer), 0);

//     // Receive data from the client
//     bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
//     if (bytes_received > 0) {
//         buffer[bytes_received] = '\0';

//         // Check the client's choice
//         int choice = atoi(buffer);
//         switch (choice) {
//             case 1:
//                 // Help: Print available options
//                 send(client_socket, "Available options:\n[1] Help\n[2] Get the current system date and time\n[3] Set a new date and time\n[0] Exit\n", strlen(buffer), 0);
//                 break;

//             case 2:
//                 // Get the current system date and time
//                 printCurrentSystemDateTime();
//                 break;

//             case 3:
//                 // Set a new date and time
//                 send(client_socket, "Enter the new date and time in the format: YYYY-MM-DD HH:MM:SS\n", strlen(buffer), 0);
//                 bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
//                 if (bytes_received > 0) {
//                     buffer[bytes_received] = '\0';
//                     int year, month, day, hour, minute, second;
//                     sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
//                     setSystemDateTime(year, month, day, hour, minute, second);
//                 }
//                 break;

//             case 0:
//                 // Exit
//                 send(client_socket, "Goodbye!\n", strlen(buffer), 0);
//                 break;

//             default:
//                 // Invalid choice
//                 send(client_socket, "Invalid choice. Enter a valid option.\n", strlen(buffer), 0);
//                 break;
//         }
//     }

//     closesocket(client_socket);
// }

// void start_network_clock_server() {
//     WSADATA wsa;
//     SOCKET server_socket, client_socket;
//     struct sockaddr_in server, client;
//     int port = read_port_from_config();
//     if (port == -1) {
//         fprintf(stderr, "Failed to read the port from the configuration file.\n");
//         return;
//     }

//     // Initialize Winsock
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//         fprintf(stderr, "Failed to initialize Winsock.\n");
//         return;
//     }

//     // Create a socket
//     if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
//         fprintf(stderr, "Failed to create socket.\n");
//         WSACleanup();
//         return;
//     }

//     // Prepare the sockaddr_in structure
//     server.sin_family = AF_INET;
//     server.sin_addr.s_addr = INADDR_ANY;
//     server.sin_port = htons(port);

//     // Bind the socket
//     if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
//         fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
//         closesocket(server_socket);
//         WSACleanup();
//         return;
//     }

//     // Listen for incoming connections
//     listen(server_socket, 3);

//     printf("Server listening on port %d...\n", port);

//     // Accept and handle incoming connections
//     int c = sizeof(struct sockaddr_in);
//     while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
//         printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

//         // Handle client request
//         handle_client(client_socket);
//     }

//     if (client_socket == INVALID_SOCKET) {
//         fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
//         closesocket(server_socket);
//         WSACleanup();
//         return;
//     }

//     // Cleanup and close the socket
//     closesocket(server_socket);
//     WSACleanup();
// }

// int main() {
//     start_network_clock_server();
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <winsock2.h>
// #include "../include/network_clock.h"
// #include "../include/time_setup.h"
// #include "../include/config.h"
// #include <process.h> // For _beginthread()

// #define MAX_BUFFER_SIZE 1024

// // void handle_client(void *data)
// // {
// //     SOCKET client_socket = (SOCKET)data;
// //     char buffer[MAX_BUFFER_SIZE];
// //     int bytes_received;

// //     // Send welcome message with options to the client
// //     char *msg = "Welcome!\nAvailable options:\n[1] Help\n[2] Set the time\n[3] Exit\nEnter your choice : ";

// //     send(client_socket, msg, strlen(msg), 0);

// //     while (1)
// //     { // Loop to handle multiple requests
// //         // Receive data from the client
// //         bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// //         if (bytes_received > 0)
// //         {
// //             buffer[bytes_received] = '\0';

// //             // Check the client's choice
// //             int choice = atoi(buffer);
// //             switch (choice)
// //             {
// //             case 1:
// //                 // Help: Print available options
// //                 send(client_socket, msg, strlen(msg), 0);
// //                 break;

// //             case 2:
// //                 // Set a new date and time
// //                 send(client_socket, "Enter the new date and time in the format: YYYY-MM-DD HH:MM:SS\n", strlen(msg), 0);
// //                 bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
// //                 if (bytes_received > 0)
// //                 {
// //                     buffer[bytes_received] = '\0';
// //                     int year, month, day, hour, minute, second;
// //                     sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
// //                     setSystemDateTime(year, month, day, hour, minute, second);
// //                 }
// //                 break;

// //             case 3:
// //                 // Exit
// //                 send(client_socket, "Goodbye!\n", strlen(msg), 0);
// //                 closesocket(client_socket);
// //                 _endthread();
// //                 break;

// //             default:
// //                 // Invalid choice
// //                 send(client_socket, "Invalid choice. Enter a valid option.\n", strlen(msg), 0);
// //                 break;
// //             }
// //         }
// //     }
// // }

// void handle_client(void* data) {
//     SOCKET client_socket = (SOCKET)data;
//     struct sockaddr_in client_addr;
//     int client_addr_len = sizeof(client_addr);
//     char buffer[MAX_BUFFER_SIZE];
//     int bytes_received;

//     // Get the client's IP address
//     getpeername(client_socket, (struct sockaddr *)&client_addr, &client_addr_len);
//     char *client_ip = inet_ntoa(client_addr.sin_addr);

//     // Send welcome message with options to the client
//     char *msg = "Welcome!\nAvailable options:\n[1] Help\n[2] Set the time\n[3] Exit\n";
//     send(client_socket, msg, strlen(msg), 0);

//     while (1) {  // Loop to handle multiple requests
//         // Receive data from the client
//         bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
//         if (bytes_received > 0) {
//             buffer[bytes_received] = '\0';

//             // Check the client's choice
//             int choice = atoi(buffer);
//             switch (choice) {
//                 case 1:
//                     // Help: Print available options
//                     send(client_socket, msg, strlen(msg), 0);
//                     break;

//                 case 2:
//                     // Check if the client is local or remote
//                     if (strcmp(client_ip, "127.0.0.1") == 0) {
//                         // Set a new date and time
//                         send(client_socket, "Enter the new date and time in the format: YYYY-MM-DD HH:MM:SS\n", strlen(msg), 0);
//                         bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
//                         if (bytes_received > 0) {
//                             buffer[bytes_received] = '\0';
//                             int year, month, day, hour, minute, second;
//                             sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
//                             setSystemDateTime(year, month, day, hour, minute, second);
//                         }
//                     } else {
//                         // If the client is remote, don't allow them to set the time
//                         send(client_socket, "Only local clients can set the time.\n", strlen(msg), 0);
//                     }
//                     break;

//                 case 3:
//                     // Exit
//                     send(client_socket, "Goodbye!\n", strlen(msg), 0);
//                     closesocket(client_socket);
//                     _endthread();
//                     break;

//                 default:
//                     // Invalid choice
//                     send(client_socket, "Invalid choice. Enter a valid option.\n", strlen(msg), 0);
//                     break;
//             }
//         }
//     }
// }

// void start_network_clock_server()
// {
//     WSADATA wsa;
//     SOCKET server_socket, client_socket;
//     struct sockaddr_in server, client;
//     int port = read_port_from_config();
//     if (port == -1)
//     {
//         fprintf(stderr, "Failed to read the port from the configuration file.\n");
//         return;
//     }

//     // Initialize Winsock
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//     {
//         fprintf(stderr, "Failed to initialize Winsock.\n");
//         return;
//     }

//     // Create a socket
//     if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
//     {
//         fprintf(stderr, "Failed to create socket.\n");
//         WSACleanup();
//         return;
//     }

//     // Prepare the sockaddr_in structure
//     server.sin_family = AF_INET;
//     server.sin_addr.s_addr = INADDR_ANY;
//     server.sin_port = htons(port);

//     // Bind the socket
//     if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
//     {
//         fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
//         closesocket(server_socket);
//         WSACleanup();
//         return;
//     }

//     // Listen for incoming connections
//     listen(server_socket, 3);

//     printf("Server listening on port %d...\n", port);

//     // Accept and handle incoming connections
//     int c = sizeof(struct sockaddr_in);
//     while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
//     {
//         printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

//         // Handle client request in a separate thread
//         _beginthread(handle_client, 0, (void *)client_socket);

//         char *client_ip = inet_ntoa(client.sin_addr);

//         // Check if the client is local or remote
//         if (strcmp(client_ip, "127.0.0.1") == 0)
//         {
//             printf("Local client connected\n");
//         }
//         else
//         {
//             printf("Remote client connected\n");
//         }
//     }

//     if (client_socket == INVALID_SOCKET)
//     {
//         fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
//         closesocket(server_socket);
//         WSACleanup();
//         return;
//     }

//     // Cleanup and close the socket
//     closesocket(server_socket);
//     WSACleanup();
// }

// int main()
// {
//     start_network_clock_server();
//     return 0;
// }



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include "../include/network_clock.h"
#include "../include/time_setup.h"
#include "../include/config.h"
#include <process.h> // For _beginthread()

#define MAX_BUFFER_SIZE 1024

void handle_client(void* data) {
    SOCKET client_socket = (SOCKET)data;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;

    // Get the client's IP address
    getpeername(client_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    char *client_ip = inet_ntoa(client_addr.sin_addr);

    // Send welcome message with options to the client
    char *msg = "Welcome!\nAvailable options:\n[1] Help\n[2] Set the time\n[3] Exit\n";
    send(client_socket, msg, strlen(msg), 0);

    while (1) {  // Loop to handle multiple requests
        // Receive data from the client
        bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';

            // Check the client's choice
            int choice = atoi(buffer);
            switch (choice) {
                case 1:
                    // Help: Print available options
                    send(client_socket, msg, strlen(msg), 0);
                    break;

                case 2:
                    // Check if the client is local or remote
                    if (strcmp(client_ip, "127.0.0.1") == 0) {
                        // Set a new date and time
                        send(client_socket, "Enter the new date and time in the format: YYYY-MM-DD HH:MM:SS\n", strlen(msg), 0);
                        bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
                        if (bytes_received > 0) {
                            buffer[bytes_received] = '\0';
                            int year, month, day, hour, minute, second;
                            sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
                            setSystemDateTime(year, month, day, hour, minute, second);
                        }
                    } else {
                        // If the client is remote, don't allow them to set the time
                        send(client_socket, "Only local clients can set the time.\n", strlen(msg), 0);
                    }
                    break;

                case 3:
                    // Exit
                    send(client_socket, "Goodbye!\n", strlen(msg), 0);
                    closesocket(client_socket);
                    _endthread();
                    break;

                default:
                    // Invalid choice
                    send(client_socket, "Invalid choice. Enter a valid option.\n", strlen(msg), 0);
                    break;
            }
        }
    }
}

void start_network_clock_server()
{
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int port = read_port_from_config();
    if (port == -1)
    {
        fprintf(stderr, "Failed to read the port from the configuration file.\n");
        return;
    }

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return;
    }

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        fprintf(stderr, "Failed to create socket.\n");
        WSACleanup();
        return;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
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
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
    {
        printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        // Handle client request in a separate thread
        _beginthread(handle_client, 0, (void *)client_socket);

        char *client_ip = inet_ntoa(client.sin_addr);

        // Check if the client is local or remote
        if (strcmp(client_ip, "127.0.0.1") == 0)
        {
            printf("Local client connected\n");
        }
        else
        {
            printf("Remote client connected\n");
        }
    }

    if (client_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return;
    }

    // Cleanup and close the socket
    closesocket(server_socket);
    WSACleanup();
}

int main()
{
    start_network_clock_server();
    return 0;
}
