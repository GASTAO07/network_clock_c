
// #include <stdio.h>
// #include <stdlib.h>
// #include "../include/security.h"
// #include <time.h>
// #include "../include/server.h"
// #include "../include/time_setup.h"
// #include <windows.h>

// // Define function that will run in a new thread
// DWORD WINAPI start_server_thread(LPVOID lpParam)
// {
//     start_network_clock_server();
//     return 0;
// }

// int main()
// {
//     // Define as permissões do arquivo de configuração
//     int result = check_and_set_config_file_permissions();
//     if (result == 0)
//     {
//         printf("Config file permissions set successfully.\n");
//     }
//     else
//     {
//         printf("Error setting config file permissions.\n");
//     }

//     // Define a data e hora do sistema
//     int year, month, day, hour, minute, second;

//     printf("Enter year: ");
//     scanf("%d", &year);
//     printf("Enter month: ");
//     scanf("%d", &month);
//     printf("Enter day: ");
//     scanf("%d", &day);
//     printf("Enter hour: ");
//     scanf("%d", &hour);
//     printf("Enter minute: ");
//     scanf("%d", &minute);
//     printf("Enter second: ");
//     scanf("%d", &second);

//     setSystemDateTime(year, month, day, hour, minute, second);

//     // Start the server in a new thread
//     HANDLE hThread;
//     DWORD dwThreadId;

//     hThread = CreateThread(
//         NULL,                   // default security attributes
//         0,                      // use default stack size  
//         start_server_thread,    // thread function name
//         NULL,                   // argument to thread function 
//         0,                      // use default creation flags 
//         &dwThreadId);           // returns the thread identifier 

//     // Check the return value for success. If something wrong...
//     if (hThread == NULL) 
//     {
//         printf("CreateThread failed (%d)\n", GetLastError());
//         return 1;
//     }

//     // Here, you could do other things, and the server thread will run concurrently

//     // Wait until child thread exits.
//     WaitForSingleObject(hThread, INFINITE);
//     CloseHandle(hThread);

//     return 0;
// }


// // version 02 
// #include <stdio.h>
// #include <stdlib.h>
// #include "../include/security.h"
// #include <time.h>
// #include "../include/server.h"
// #include "../include/time_setup.h"
// #include <windows.h>
// #include <conio.h>

// // Define function that will run in a new thread
// DWORD WINAPI start_server_thread(LPVOID lpParam)
// {
//     start_network_clock_server();
//     return 0;
// }

// void ask_for_time() {
//     int year, month, day, hour, minute, second;

//     printf("Enter year: ");
//     scanf("%d", &year);
//     printf("Enter month: ");
//     scanf("%d", &month);
//     printf("Enter day: ");
//     scanf("%d", &day);
//     printf("Enter hour: ");
//     scanf("%d", &hour);
//     printf("Enter minute: ");
//     scanf("%d", &minute);
//     printf("Enter second: ");
//     scanf("%d", &second);

//     setSystemDateTime(year, month, day, hour, minute, second);
// }

// int main()
// {
//     char userInput;
//     // Start the server in a new thread
//     HANDLE hThread;
//     DWORD dwThreadId;

//     hThread = CreateThread(
//         NULL,                   // default security attributes
//         0,                      // use default stack size  
//         start_server_thread,    // thread function name
//         NULL,                   // argument to thread function 
//         0,                      // use default creation flags 
//         &dwThreadId);           // returns the thread identifier 

//     // Check the return value for success. If something wrong...
//     if (hThread == NULL) 
//     {
//         printf("CreateThread failed (%d)\n", GetLastError());
//         return 1;
//     }

//     printf("Server started...\n");

//     while(1) {
//         printf("Do you want to set the time? (y/n): ");
//         scanf(" %c", &userInput); // The space before %c helps to skip any leftover '\n' in the buffer

//         if(userInput == 'y' || userInput == 'Y') {
//             ask_for_time();
//         } else if(userInput == 'n' || userInput == 'N') {
//             printf("Continuing to listen on the port...\n");
//             continue;
//         } else if(userInput == 27) { // ASCII code for 'Esc' key
//             printf("Exiting...\n");
//             TerminateThread(hThread, 0);
//             CloseHandle(hThread);
//             break;
//         } else {
//             printf("Invalid input. Please enter 'y' or 'n'...\n");
//         }
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include "../include/security.h"
#include <time.h>
#include "../include/server.h"
#include "../include/time_setup.h"
#include <windows.h>
#include <conio.h>

// Define function that will run in a new thread
DWORD WINAPI start_server_thread(LPVOID lpParam)
{
    start_network_clock_server();
    return 0;
}

void ask_for_time() {
    int year, month, day, hour, minute, second;

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
}

int main()
{
    char userInput;
    // Start the server in a new thread
    HANDLE hThread;
    DWORD dwThreadId;

    hThread = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        start_server_thread,    // thread function name
        NULL,                   // argument to thread function 
        0,                      // use default creation flags 
        &dwThreadId);           // returns the thread identifier 

    // Check the return value for success. If something wrong...
    if (hThread == NULL) 
    {
        printf("CreateThread failed (%d)\n", GetLastError());
        return 1;
    }

    printf("Server started...\n");
    Sleep(1000); // Wait for 1 second

    while(1) {
        printf("Do you want to set the time? (y/n): ");
        scanf(" %c", &userInput); // The space before %c helps to skip any leftover '\n' in the buffer

        if(userInput == 'y' || userInput == 'Y') {
            ask_for_time();
        } else if(userInput == 'n' || userInput == 'N') {
            printf("Continuing to listen on the port...\n");
            Sleep(1000); // Wait for 1 second before next iteration
            continue;
        } else if(userInput == 27) { // ASCII code for 'Esc' key
            printf("Exiting...\n");
            TerminateThread(hThread, 0);
            CloseHandle(hThread);
            break;
        } else {
            printf("Invalid input. Please enter 'y' or 'n'...\n");
        }
    }

    return 0;
}
