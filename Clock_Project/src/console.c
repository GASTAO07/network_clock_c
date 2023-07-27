// // // #include "../include/console.h"
// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include "../include/server.h" // Include the header file for the server functionality

// // // // Function to start the console and handle user input for the server
// // // void start_console()
// // // {
// // //     printf("Server console started. Type 'help' for a list of commands.\n");

// // //     char input[256];
// // //     while (1)
// // //     {
// // //         printf("> ");
// // //         fgets(input, sizeof(input), stdin);

// // //         // Remove the trailing newline character from the input
// // //         int input_length = strlen(input);
// // //         if (input[input_length - 1] == '\n')
// // //         {
// // //             input[input_length - 1] = '\0';
// // //         }

// // //         // Handle commands based on user input
// // //         if (strcmp(input, "help") == 0)
// // //         {
// // //             printf("Available commands:\n");
// // //             printf("  help - Show this help message.\n");
// // //             printf("  start_server - Start the network clock server.\n");
// // //             printf("  exit - Exit the program.\n");
// // //         }
// // //         else if (strcmp(input, "start_server") == 0)
// // //         {
// // //             printf("Starting the network clock server...\n");
// // //             start_network_clock_server();
// // //         }
// // //         else if (strcmp(input, "exit") == 0)
// // //         {
// // //             printf("Exiting the program...\n");
// // //             break;
// // //         }
// // //         else
// // //         {
// // //             printf("Invalid command. Type 'help' for a list of commands.\n");
// // //         }
// // //     }
// // // }
// // #include "../include/console.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include "../include/server.h" // Include the header file for the server functionality
// // #include "../include/time_setup.h" // Include the header file for setting the system time

// // // Function to print the menu options
// // void print_menu() {
// //     printf("\n");
// //     printf("[1] Help\n");
// //     printf("[2] Start the server\n");
// //     printf("[3] Set the time\n");
// //     printf("[0] Exit\n");
// // }

// // // Function to start the console and handle user input for the server
// // void start_console()
// // {
// //     printf("Server console started. Type 'help' for a list of commands.\n");

// //     char input[256];
// //     while (1)
// //     {
// //         print_menu();
// //         printf("> ");
// //         fgets(input, sizeof(input), stdin);

// //         // Remove the trailing newline character from the input
// //         int input_length = strlen(input);
// //         if (input[input_length - 1] == '\n')
// //         {
// //             input[input_length - 1] = '\0';
// //         }

// //         // Handle commands based on user input
// //         if (strcmp(input, "1") == 0 || strcmp(input, "help") == 0)
// //         {
// //             printf("Available commands:\n");
// //             printf("  [1] Help - Show this help message.\n");
// //             printf("  [2] Start the server - Start the network clock server.\n");
// //             printf("  [3] Set the time - Set the system time.\n");
// //             printf("  [0] Exit - Exit the program.\n");
// //         }
// //         else if (strcmp(input, "2") == 0 || strcmp(input, "start the server") == 0)
// //         {
// //             printf("Starting the network clock server...\n");
// //             start_network_clock_server();
// //         }
// //         else if (strcmp(input, "3") == 0 || strcmp(input, "set the time") == 0)
// //         {
// //             int year, month, day, hour, minute, second;

// //             printf("Enter year: ");
// //             scanf("%d", &year);
// //             printf("Enter month: ");
// //             scanf("%d", &month);
// //             printf("Enter day: ");
// //             scanf("%d", &day);
// //             printf("Enter hour: ");
// //             scanf("%d", &hour);
// //             printf("Enter minute: ");
// //             scanf("%d", &minute);
// //             printf("Enter second: ");
// //             scanf("%d", &second);

// //             setSystemDateTime(year, month, day, hour, minute, second);
// //         }
// //         else if (strcmp(input, "0") == 0 || strcmp(input, "exit") == 0)
// //         {
// //             printf("Exiting the program...\n");
// //             break;
// //         }
// //         else
// //         {
// //             printf("Invalid command. Type 'help' for a list of commands.\n");
// //         }
// //     }
// // }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "../include/server.h"
// #include "../include/time_setup.h"
// #include "../include/config.h" // Include the header file for reading the port from the configuration file
// #include "../include/network_clock_server.h" // Include the new header for the server thread function

// void printMenu() {
//     printf("\n[1] Help\n");
//     printf("[2] Start the server\n");
//     printf("[3] Set the time\n");
//     printf("[0] Exit\n");
// }

// void start_console() {
//     char userInput;
//     int port = read_port_from_config();
//     if (port == -1) {
//         fprintf(stderr, "Failed to read the port from the configuration file.\n");
//         return;
//     }

//     printMenu();

//     while (1) {
//         printf("> ");
//         scanf(" %c", &userInput); // The space before %c helps to skip any leftover '\n' in the buffer

//         switch (userInput) {
//             case '1':
//                 printMenu();
//                 break;
//             case '2':
//                 start_network_clock_server_thread((LPVOID)port);
//                 break;
//             case '3':
//                 {
//                     int year, month, day, hour, minute, second;

//                     printf("Enter year: ");
//                     scanf("%d", &year);
//                     printf("Enter month: ");
//                     scanf("%d", &month);
//                     printf("Enter day: ");
//                     scanf("%d", &day);
//                     printf("Enter hour: ");
//                     scanf("%d", &hour);
//                     printf("Enter minute: ");
//                     scanf("%d", &minute);
//                     printf("Enter second: ");
//                     scanf("%d", &second);

//                     setSystemDateTime(year, month, day, hour, minute, second);
//                     break;
//                 }
//             case '0':
//                 printf("Exiting...\n");
//                 return;
//             default:
//                 printf("Invalid input. Please try again.\n");
//         }
//     }
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/server.h"
#include "../include/time_setup.h"
#include "../include/config.h" // Include the header file for reading the port from the configuration file

// ... (unchanged code)

void printMenu() {
    printf("\n[1] Help\n");
    printf("[2] Start the server\n");
    printf("[3] Set the time\n");
    printf("[0] Exit\n");
}

void start_console() {
    char userInput;
    int port = read_port_from_config();
    if (port == -1) {
        fprintf(stderr, "Failed to read the port from the configuration file.\n");
        return;
    }
    
    printMenu();

    while (1) {
        printf("> ");
        scanf(" %c", &userInput); // The space before %c helps to skip any leftover '\n' in the buffer

        switch (userInput) {
            case '1':
                printMenu();
                break;
            case '2':
                start_network_clock_server(); // Start the network clock server
                break;
            case '3':
                {
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
                    break;
                }
            case '0':
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid input. Please try again.\n");
        }
    }
}
