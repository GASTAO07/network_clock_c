#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/server.h"
#include "../include/time_setup.h"
#include "../include/config.h"

void printMenu() // <-----------------------------------------
{
    printf("\n[1] Help\n");
    printf("[2] Start the server\n");
    printf("[3] Set the time\n");
    printf("[0] Exit\n");
}

void start_console()
{
    char userInput;
    int port = read_port_from_config();
    if (port == -1)
    {
        fprintf(stderr, "Failed to read the port from the configuration file.\n");
        return;
    }

    printMenu();

    while (1)
    {
        printf("> ");
        scanf(" %c", &userInput);
        switch (userInput)
        {
        case '1':
            printMenu();
            break;
        case '2':
            start_network_clock_server();
            break;
        case '3':
        {
            int year, month, day, hour, minute, second; // <-----------------------------------------

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
