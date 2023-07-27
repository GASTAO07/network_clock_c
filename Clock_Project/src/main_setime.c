#include <stdio.h>
#include <stdlib.h>
#include "../include/security.h"
#include <time.h>
#include "../include/server.h"
#include "../include/time_setup.h"
#include <windows.h>
#include <conio.h>
#include "../include/config.h"

DWORD WINAPI start_server_thread(LPVOID lpParam) {
    int port = (int)lpParam;

    if (check_and_set_config_file_permissions() == -1) {
        fprintf(stderr, "Failed to set permissions for the configuration file.\n");
        return 1;
    }

    start_network_clock_server(port);

    return 0;
}

int main() {
    char userInput;

    int port = read_port_from_config();
    if (port == -1) {
        fprintf(stderr, "Failed to read the port from the configuration file.\n");
        return 1;
    }

    printf("\n[1] Help\n"); // <-----------------------------------------
    printf("[2] Start the server\n");
    printf("[3] Set the time\n");
    printf("[0] Exit\n");

    HANDLE hThread;
    DWORD dwThreadId;

    hThread = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size
        start_server_thread,    // thread function name
        (LPVOID)port,           // argument to thread function
        0,                      // use default creation flags
        &dwThreadId);           // returns the thread identifier

    if (hThread == NULL) {
        printf("CreateThread failed (%lu)\n", GetLastError());
        return 1;
    }

    printf("Server started...\n");
    Sleep(1000); 
    while (1) {
        printf("\n[1] Help\n");// <-----------------------------------------
        printf("[2] Start the server\n");
        printf("[3] Set the time\n");
        printf("[0] Exit\n");
        
        printf("> ");
        scanf(" %c", &userInput); 
        switch (userInput) {
            case '1':
                break;
            case '2':
                printf("Starting the server...\n");
                break;
            case '3':
                {
                    int year, month, day, hour, minute, second;// <-----------------------------------------

                    printf("Enter year: "); 
                    scanf("%d", &year);
                    printf("Enter month: ");
                    scanf("%d", &month);
                    printf("Enter day: ");
                    scanf("%d", &day);
                    printf("Enter hour: ");
                    scanf("%d", &hour);
                    printf("Enter minute: ");
                    scanf("%d", &minute);
                    printf("Enter second: ");
                    scanf("%d", &second);

                    setSystemDateTime(year, month, day, hour, minute, second);
                    break;
                }
            case '0':
                printf("Exiting...\n");
                TerminateThread(hThread, 0);
                CloseHandle(hThread);
                return 0;
            default:
                printf("Invalid input. Please enter a valid option.\n");
        }
    }

    return 0;
}
