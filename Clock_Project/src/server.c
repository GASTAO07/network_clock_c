// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <winsock2.h>
// #include "../include/network_clock.h"
// #include "../include/time_setup.h"
// #include "../include/config.h"
// #include <process.h>
// #include <time.h>

// #define MAX_BUFFER_SIZE 1024

// void format_time(const char *format, char *output)
// {
//     time_t t = time(NULL);
//     struct tm *tm_info = localtime(&t);

//     if (strcmp(format, "HH:MM:SS") == 0)
//     {
//         strftime(output, 26, "%H:%M:%S", tm_info);
//     }
//     else if (strcmp(format, "HH:MM") == 0)
//     {
//         strftime(output, 26, "%H:%M", tm_info);
//     }
//     else if (strcmp(format, "HHMMSS") == 0)
//     {
//         strftime(output, 26, "%H%M%S", tm_info);
//     }
//     else if (strcmp(format, "HHMM") == 0)
//     {
//         strftime(output, 26, "%H%M", tm_info);
//     }
//     else if (strcmp(format, "YYYY-MM-DD HH:MM:SS") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H:%M:%S", tm_info);
//     }
//     else if (strcmp(format, "YYYY-MM-DD HH:MM") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H:%M", tm_info);
//     }
//     else if (strcmp(format, "YYYY-MM-DD") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d", tm_info);
//     }
//     else
//     {
//         strcpy(output, "Invalid time format! Please try again.\n");
//     }
// }

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include "../include/network_clock.h"
#include "../include/time_setup.h"
#include "../include/config.h"
#include <process.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024

void format_time(const char *format, char *output)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (strcmp(format, "HH:MM:SS") == 0)
    {
        strftime(output, 26, "%H:%M:%S", tm_info);
    }
    else if (strcmp(format, "HH:MM") == 0)
    {
        strftime(output, 26, "%H:%M", tm_info);
    }
    else if (strcmp(format, "HHMMSS") == 0)
    {
        strftime(output, 26, "%H%M%S", tm_info);
    }
    else if (strcmp(format, "HHMM") == 0)
    {
        strftime(output, 26, "%H%M", tm_info);
    }
    else if (strcmp(format, "YYYY-MM-DD HH:MM:SS") == 0)
    {
        strftime(output, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    }
    else if (strcmp(format, "YYYY-MM-DD HH:MM") == 0)
    {
        strftime(output, 26, "%Y-%m-%d %H:%M", tm_info);
    }
    else if (strcmp(format, "YYYY-MM-DD") == 0)
    {
        strftime(output, 26, "%Y-%m-%d", tm_info);
    }
    else
    {
        strcpy(output, "Invalid time format! Please try again.\n");
    }
}

// ... (Rest of your original server code) ...

void handle_client(void *data)
{
    SOCKET client_socket = (SOCKET)data;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;

    // Get the client's IP address
    getpeername(client_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    char *client_ip = inet_ntoa(client_addr.sin_addr);

    // Send welcome message with options to the client
    char *welcome_msg = "Welcome! \r\n";
    char *options_msg = "Available options:\r\n[1] Help\r\n[2] Set the time\r\n[3] Change format time\r\n[4] Exit\r\n";

    // Check if the client is local or remote
    if (strcmp(client_ip, "127.0.0.1") == 0)
    {
        char time_str[100];
        getSystemDateTime(time_str);
        send(client_socket, time_str, strlen(time_str), 0);
        send(client_socket, welcome_msg, strlen(welcome_msg), 0);
        send(client_socket, options_msg, strlen(options_msg), 0);
    }
    else
    {
        // For remote clients, send the current server time immediately
        char time_str[100];
        getSystemDateTime(time_str);
        send(client_socket, time_str, strlen(time_str), 0);
    }

    while (1)
    { // Loop to handle multiple requests
        // Receive data from the client
        bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);

        if (bytes_received > 0)
        {
            buffer[bytes_received] = '\0';

            // Check the client's choice
            int choice = atoi(buffer);
            switch (choice)
            {
            case 1:
                // Help: Print available options
                send(client_socket, options_msg, strlen(options_msg), 0);
                break;

            case 2:
                // Check if the client is local or remote
                if (strcmp(client_ip, "127.0.0.1") == 0)
                {
                    // Set a new date and time
                    send(client_socket, "Enter the new date and time in the format: YYYY-MM-DD HH:MM:SS\r\n", strlen(options_msg), 0);
                    bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
                    if (bytes_received > 0)
                    {
                        buffer[bytes_received] = '\0';
                        int year, month, day, hour, minute, second;
                        sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
                        setSystemDateTime(year, month, day, hour, minute, second);
                    }
                }
                else
                {
                    // If the client is remote, don't allow them to set the time
                    send(client_socket, "Only local clients can set the time.\r\n", strlen(options_msg), 0);
                }
                break;
            case 3:
                // Change time format
                send(client_socket, "Enter the new time format (HH:MM:SS, HH:MM, HHMMSS, HHMM, YYYY-MM-DD HH:MM:SS, YYYY-MM-DD)\r\n", strlen(options_msg), 0);
                bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
                if (bytes_received > 0)
                {
                    buffer[bytes_received] = '\0';
                    printf("Received time format: %s\r\n", buffer); // Debug log

                    // Check if the format is one of the accepted formats
                    if (strcmp(buffer, "HH:MM:SS") == 0 || strcmp(buffer, "HH:MM") == 0 ||
                        strcmp(buffer, "HHMMSS") == 0 || strcmp(buffer, "HHMM") == 0 ||
                        strcmp(buffer, "YYYY-MM-DD HH:MM:SS") == 0 || strcmp(buffer, "YYYY-MM-DD") == 0)
                    {
                        char formatted_time[100];
                        format_time(buffer, formatted_time);
                        send(client_socket, formatted_time, strlen(formatted_time), 0);
                    }

                    else
                    {
                        // If the format is not accepted, send an error message
                        send(client_socket, "Invalid time format! Please try again.\r\n", strlen("Invalid time format! Please try again.\r\n"), 0);
                    }
                }
                break;

            case 4:
                // Exit
                send(client_socket, "Goodbye!\r\n", strlen(options_msg), 0);
                closesocket(client_socket);
                _endthread();
                break;
            }
        }
    }
}

void start_network_clock_server() // <-----------------------------------------
{
    WSADATA wsa; // <-----------------------------------------
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
        if (strcmp(client_ip, "127.0.0.1") == 0) // <-----------------------------------------
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



// void format_time(const char *format, char *output)
// {
//     time_t t = time(NULL);
//     struct tm *tm_info = localtime(&t);

//     if (strcmp(format, "HH:MM:SS") == 0)
//     {
//         strftime(output, 26, "%H:%M:%S", tm_info);
//     }
//     else if (strcmp(format, "HH:MM") == 0)
//     {
//         strftime(output, 26, "%H:%M", tm_info);
//     }
//     else if (strcmp(format, "HHMMSS") == 0)
//     {
//         strftime(output, 26, "%H%M%S", tm_info);
//     }
//     else if (strcmp(format, "HHMM") == 0)
//     {
//         strftime(output, 26, "%H%M", tm_info);
//     }
//     else if (strcmp(format, "YYYY-MM-DD HH:MM:SS") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H:%M:%S", tm_info);
//     }
//     else if (strcmp(format, "YYYY-MM-DD HH:MM") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H:%M", tm_info);
//     }
//     else if (strcmp(format, "YYYY-MM-DD") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d", tm_info);
//     }
//     else
//     {
//         strcpy(output, "Invalid time format! Please try again.\n");
//     }
// }


// void format_time(const char *format, char *output)
// {
//     time_t t = time(NULL);
//     struct tm *tm_info = localtime(&t);

//     if (strcmp(format, "%H:%M:%S") == 0)
//     {
//         strftime(output, 26, "%H:%M:%S\n", tm_info);
//     }
//     else if (strcmp(format, "%H:%M") == 0)
//     {
//         strftime(output, 26, "%H:%M\n", tm_info);
//     }
//     else if (strcmp(format, "%H%M%S") == 0)
//     {
//         strftime(output, 26, "%H%M%S\n", tm_info);
//     }
//     else if (strcmp(format, "%H%M") == 0)
//     {
//         strftime(output, 26, "%H%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m-%d %H:%M:%S") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H:%M:%S\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m %H:%M:%S") == 0)
//     {
//         strftime(output, 26, "%Y-%m %H:%M:%S\n", tm_info);
//     }
//     else if (strcmp(format, "%Y %H:%M:%S") == 0)
//     {
//         strftime(output, 26, "%Y %H:%M:%S\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m-%d %H%M%S") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H%M%S\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m %H%M%S") == 0)
//     {
//         strftime(output, 26, "%Y-%m %H%M%S\n", tm_info);
//     }
//     else if (strcmp(format, "%Y %H%M%S") == 0)
//     {
//         strftime(output, 26, "%Y %H%M%S\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m-%d %H%M") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m %H%M") == 0)
//     {
//         strftime(output, 26, "%Y-%m %H%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y %H%M") == 0)
//     {
//         strftime(output, 26, "%Y %H%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m-%d %H:%M") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d %H:%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m %H:%M") == 0)
//     {
//         strftime(output, 26, "%Y-%m %H:%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y %H:%M") == 0)
//     {
//         strftime(output, 26, "%Y %H:%M\n", tm_info);
//     }
//     else if (strcmp(format, "%Y-%m-%d") == 0)
//     {
//         strftime(output, 26, "%Y-%m-%d\n", tm_info);
//     }
//     else
//     {
//         strcpy(output, "Invalid time format! Please try again.\n");
//     }
// }


// void format_time(const char *format, char *output)
// {
//     time_t t = time(NULL);
//     struct tm *tm_info = localtime(&t);

    //     if (strcmp(format, "HH:MM:SS") == 0)
    //     {
    //         strftime(output, 26, "%H:%M:%S\n", tm_info);
    //     }
    //     else if (strcmp(format, "HH:MM") == 0)
    //     {
    //         strftime(output, 26, "%H:%M\n", tm_info);
    //     }
    //     else if (strcmp(format, "HHMMSS") == 0)
    //     {
    //         strftime(output, 26, "%H%M%S\n", tm_info);
    //     }
    //     else if (strcmp(format, "HHMM") == 0)
    //     {
    //         strftime(output, 26, "%H%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM-DD HH:MM:SS") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m-%d %H:%M:%S\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM HH:MM:SS") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m %H:%M:%S\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY HH:MM:SS") == 0)
    //     {
    //         strftime(output, 26, "%Y %H:%M:%S\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM-DD HHMMSS") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m-%d %H%M%S\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM HHMMSS") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m %H%M%S\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY HHMMSS") == 0)
    //     {
    //         strftime(output, 26, "%Y %H%M%S\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM-DD HHMM") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m-%d %H%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM HHMM") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m %H%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY HHMM") == 0)
    //     {
    //         strftime(output, 26, "%Y %H%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM-DD HH:MM") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m-%d %H:%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM HH:MM") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m %H:%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY HH:MM") == 0)
    //     {
    //         strftime(output, 26, "%Y %H:%M\n", tm_info);
    //     }

    //     else if (strcmp(format, "YYYY-MM-DD") == 0)
    //     {
    //         strftime(output, 26, "%Y-%m-%d\n", tm_info);
    //     }
    //     else
    //     {
    //         strcpy(output, "Invalid time format! Please try again.\n");
    //     }
    // }