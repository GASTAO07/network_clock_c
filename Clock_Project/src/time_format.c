#include <stdio.h>
#include <string.h>
#include <time.h>

int format_time(const char *date_format, const char *time_format, char *output) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char combined_format[100];

    // Verify the date format
    if (strcmp(date_format, "YYYY-MM-DD") == 0) {
        strcpy(combined_format, "%Y-%m-%d");
    } else if (strcmp(date_format, "YYYY/MM/DD") == 0) {
        strcpy(combined_format, "%Y/%m/%d");
    } else {
        return 0;
    }

    // Add a space between the date and time formats
    strcat(combined_format, " ");

    // Verify the time format
    if (strcmp(time_format, "HH:MM:SS") == 0) {
        strcat(combined_format, "%H:%M:%S");
    } else if (strcmp(time_format, "HH:MM") == 0) {
        strcat(combined_format, "%H:%M");
    } else if (strcmp(time_format, "HHMMSS") == 0) {
        strcat(combined_format, "%H%M%S");
    } else if (strcmp(time_format, "HHMM") == 0) {
        strcat(combined_format, "%H%M");
    } else {
        return 0;
    }

    strftime(output, 26, combined_format, tm_info);
    return 1;
}

int main() {
    char date_format[50];
    char time_format[50];
    char output[100];

    printf("Enter the new date format (YYYY-MM-DD, YYYY/MM/DD):\n");
    fgets(date_format, sizeof(date_format), stdin);
    date_format[strcspn(date_format, "\n")] = 0;

    printf("Enter the new time format (HH:MM:SS, HH:MM, HHMMSS, HHMM):\n");
    fgets(time_format, sizeof(time_format), stdin);
    time_format[strcspn(time_format, "\n")] = 0;

    if (format_time(date_format, time_format, output)) {
        printf("Formatted time: %s\n", output);
    } else {
        printf("Invalid time format! Please try again.\n");
    }

    return 0;
}
