#include "../include/console.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/server.h" // Include the header file for the server functionality

// Function to start the console and handle user input for the server
void start_console()
{
    printf("Server console started. Type 'help' for a list of commands.\n");

    char input[256];
    while (1)
    {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        // Remove the trailing newline character from the input
        int input_length = strlen(input);
        if (input[input_length - 1] == '\n')
        {
            input[input_length - 1] = '\0';
        }

        // Handle commands based on user input
        if (strcmp(input, "help") == 0)
        {
            printf("Available commands:\n");
            printf("  help - Show this help message.\n");
            printf("  start_server - Start the network clock server.\n");
            printf("  exit - Exit the program.\n");
        }
        else if (strcmp(input, "start_server") == 0)
        {
            printf("Starting the network clock server...\n");
            start_network_clock_server();
        }
        else if (strcmp(input, "exit") == 0)
        {
            printf("Exiting the program...\n");
            break;
        }
        else
        {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }
}