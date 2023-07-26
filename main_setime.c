#include <stdio.h>
#include <stdlib.h>
#include "security.h"
#include "time_setup.h"

int main() {
    // Define as permissões do arquivo de configuração
    int result = check_and_set_config_file_permissions();
    if (result == 0) {
        printf("Config file permissions set successfully.\n");
    } else {
        printf("Error setting config file permissions.\n");
    }

    // Define a data e hora do sistema
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

    return 0;
}
