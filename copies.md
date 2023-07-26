/* main_setime.c
#include "security.h"
#include <stdio.h>

int main(){
    int result = check_and_set_config_file_permissions();
    if(result == 0){
        printf("Config file succ\n");
    }else {
        printf("Error config file\n");

    }
    return0;
}

*/

/*time_setup.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

void set_system_time(const char *time_str)
{
#ifdef _WIN32

    struct tm new_time;
    strptime(time_str, "%Y-%m-%d %H:%M:%S", &new_time);

    time_t raw_time;
    time(&raw_time);

    struct tm *current_time = localtime(&raw_time);

    current_time->tm_hour = new_time.tm_hour;

    current_time->tm_min = new_time.tm_min;
    current_time->tm_sec = new_time.tm_sec;
    current_time->tm_year = new_time.tm_year;
    current_time->tm_mon = new_time.tm_mon;
    current_time->tm_mday = new_time.tm_mday;

    time_t adjusted_time = mktime(current_time);

    if (adjusted_time != (time_t)-1)
    {
        SYSTEMTIME system_time;

        system_time.wYear = (current_time->tm_year + 1900),
        system_time.wMonth = current_time->tm_mon + 1,
        system_time.wDayOfWeek = current_time->tm_wday,
        system_time.wDay = current_time->tm_mday,
        system_time.wHour = current_time->tm_hour,
        system_time.wMinute = current_time->tm_min,
        system_time.wSecond = current_time->tm_sec,
        system_time.wMilliseconds = 0;

        if (!SetSystemTime(&system_time))
        {
            fprintf(stderr, "Error setting system time: %lu\n", GetLastError());
        }
    }
#endif
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: time_setup <tempo>\n");
        printf("Exemplo: time_setup 2023-07-24 12:34:56\n");
        return 1;
    }

    const char *time_str = argv[1];

    set_system_time(time_str);

#ifdef _WIN32
    system("pause");

#endif

    return 0;

}

*/

/*version 2 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

void set_system_time(const char *time_str)
{
#ifdef _WIN32

    int year, month, day, hour, minute, second;
    
    SYSTEMTIME system_time;

    int result = sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    if (result != 6)
    {
        fprintf(stderr, "Invalid date %s\n", time_str);
        return;
    }

    // strptime(time_str, "%Y-%m-%d %H:%M:%S", &new_time);

    // time_t raw_time;
    // time(&raw_time);

    // struct tm *current_time = localtime(&raw_time);

    // current_time->tm_hour = new_time.tm_hour;
    // current_time->tm_min = new_time.tm_min;
    // current_time->tm_sec = new_time.tm_sec;
    // current_time->tm_year = new_time.tm_year;
    // current_time->tm_mon = new_time.tm_mon;
    // current_time->tm_mday = new_time.tm_mday;

    // time_t adjusted_time = mktime(current_time);

    // if (adjusted_time != (time_t)-1)
    // {

    // system_time.wYear = (current_time->tm_year + 1900),
    // system_time.wMonth = current_time->tm_mon + 1,
    // system_time.wDayOfWeek = current_time->tm_wday,
    // system_time.wDay = current_time->tm_mday,
    // system_time.wHour = current_time->tm_hour,
    // system_time.wMinute = current_time->tm_min,
    // system_time.wSecond = current_time->tm_sec,
    // system_time.wMilliseconds = 0;

    system_time.wYear = year;
    system_time.wMonth = month;
    system_time.wDay = day;
    system_time.wHour = hour;
    system_time.wMinute = minute;
    system_time.wSecond = second;
    system_time.wMilliseconds = 0;

    if (!SetSystemTime(&system_time))
    {
        fprintf(stderr, "Error setting system time: %lu\n", GetLastError());
    }
#endif
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: time_setup <tempo>\n");
        printf("Exemplo: time_setup 2023-07-24 12:34:56\n");
        return 1;
    }

    const char *time_str = argv[1];

    set_system_time(time_str);

#ifdef _WIN32
    system("pause");

#endif

    return 0;
}

*/

/*v3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

void set_system_time(const char *time_str)
{
#ifdef _WIN32

    int year, month, day, hour, minute, second;
    
    SYSTEMTIME system_time;

    int result = sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    if (result != 6)
    {
        fprintf(stderr, "Invalid date %s\n", time_str);
        return;
    }

    // strptime(time_str, "%Y-%m-%d %H:%M:%S", &new_time);

    // time_t raw_time;
    // time(&raw_time);

    // struct tm *current_time = localtime(&raw_time);

    // current_time->tm_hour = new_time.tm_hour;
    // current_time->tm_min = new_time.tm_min;
    // current_time->tm_sec = new_time.tm_sec;
    // current_time->tm_year = new_time.tm_year;
    // current_time->tm_mon = new_time.tm_mon;
    // current_time->tm_mday = new_time.tm_mday;

    // time_t adjusted_time = mktime(current_time);

    // if (adjusted_time != (time_t)-1)
    // {

    // system_time.wYear = (current_time->tm_year + 1900),
    // system_time.wMonth = current_time->tm_mon + 1,
    // system_time.wDayOfWeek = current_time->tm_wday,
    // system_time.wDay = current_time->tm_mday,
    // system_time.wHour = current_time->tm_hour,
    // system_time.wMinute = current_time->tm_min,
    // system_time.wSecond = current_time->tm_sec,
    // system_time.wMilliseconds = 0;

GetLocalTime(&system_time);

    system_time.wYear = year;
    system_time.wMonth = month;
    system_time.wDay = day;
    system_time.wHour = hour;
    system_time.wMinute = minute;
    system_time.wSecond = second;
    system_time.wMilliseconds = 0;

    if (!SetLocalTime(&system_time))
    {
        fprintf(stderr, "Error setting system time: %lu\n", GetLastError());
    }
#endif
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: time_setup <tempo>\n");
        printf("Exemplo: time_setup 2023-07-24 12:34:56\n");
        return 1;
    }

    const char *time_str = argv[1];

    set_system_time(time_str);

#ifdef _WIN32
    system("pause");

#endif

    return 0;
}

/*v4
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif
int parse_date_time(const char *time_str, struct tm *tm_time)
{
    int year, month, day, hour, minute, second;
    if (sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6)
    {
        return 0;
    }

    tm_time->tm_hour = hour;
    tm_time->tm_min = minute;
    tm_time->tm_sec = second;
    tm_time->tm_year = year - 1900;
    tm_time->tm_mon = month - 1;
    tm_time->tm_mday = day;

    return 1;
}
void set_system_time(const char *time_str)
{
#ifdef _WIN32
    struct tm tm_time;
    // SYSTEMTIME system_time;

    // int result = sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    // if (result != 6)
    // {
    //     fprintf(stderr, "Invalid date %s\n", time_str);
    //     return;
    // }

    if (!parse_date_time(time_str, &tm_time))
    {
        fprintf(stderr, "Invalid date %s\n", time_str);
        return;
    }

    // year = (tm_time.tm_year + 1900);
    // month = tm_time.tm_mon + 1;
    // day = tm_time.tm_mday;

    // hour = tm_time.tm_hour;
    // minute = tm_time.tm_min;
    // second = tm_time.tm_sec;

    // time_t raw_time;
    // time(&raw_time);

    // struct tm *current_time = localtime(&raw_time);

    // current_time->tm_hour = new_time.tm_hour;
    // current_time->tm_min = new_time.tm_min;
    // current_time->tm_sec = new_time.tm_sec;
    // current_time->tm_year = new_time.tm_year;
    // current_time->tm_mon = new_time.tm_mon;
    // current_time->tm_mday = new_time.tm_mday;

    // time_t adjusted_time = mktime(current_time);

    // if (adjusted_time != (time_t)-1)
    // {

    // system_time.wYear = (current_time->tm_year + 1900),
    // system_time.wMonth = current_time->tm_mon + 1,
    // system_time.wDayOfWeek = current_time->tm_wday,
    // system_time.wDay = current_time->tm_mday,
    // system_time.wHour = current_time->tm_hour,
    // system_time.wMinute = current_time->tm_min,
    // system_time.wSecond = current_time->tm_sec,
    // system_time.wMilliseconds = 0;

    SYSTEMTIME system_time;
    GetLocalTime(&system_time);

    system_time.wYear = tm_time.tm_year + 1900;
    system_time.wMonth = tm_time.tm_mon +1;
    system_time.wDay = tm_time.tm_mday;
    system_time.wHour = tm_time.tm_hour;
    system_time.wMinute = tm_time.tm_min;
    system_time.wSecond = tm_time.tm_sec;
    system_time.wMilliseconds = 0;

    if (!SetSystemTime(&system_time))
    {
        fprintf(stderr, "Error setting system time: %lu\n", GetLastError());
    }
#endif
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: time_setup <tempo>\n");
        printf("Exemplo: time_setup 2023-07-24 12:34:56\n");
        return 1;
    }

    const char *time_str = argv[1];

    set_system_time(time_str);

#ifdef _WIN32
    system("pause");

#endif

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// #ifdef _WIN32
// #include <Windows.h>
// #endif
// int parse_date_time(const char *time_str, struct tm *tm_time)
// {
//     struct tm tm_time = {0};

//     int year, month, day, hour, minute, second;
//     if (sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6)
//     {
//         return 0;
//     }
//     tm_time->tm_year = year - 1900;
//     tm_time->tm_mon = month - 1;
//     tm_time->tm_mday = day;
//     tm_time->tm_hour = hour;
//     tm_time->tm_min = minute;
//     tm_time->tm_sec = second;

//     return 1;
// }
// void set_system_time(const char *time_str)
// {
// #ifdef _WIN32
//     struct tm tm_time;
//     // SYSTEMTIME system_time;

//     // int result = sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
//     // if (result != 6)
//     // {
//     //     fprintf(stderr, "Invalid date %s\n", time_str);
//     //     return;
//     // }

//     if (!parse_date_time(time_str, &tm_time))
//     {
//         fprintf(stderr, "Invalid date %s\n", time_str);
//         return;
//     }

//     // year = (tm_time.tm_year + 1900);
//     // month = tm_time.tm_mon + 1;
//     // day = tm_time.tm_mday;

//     // hour = tm_time.tm_hour;
//     // minute = tm_time.tm_min;
//     // second = tm_time.tm_sec;

//     // time_t raw_time;
//     // time(&raw_time);

//     // struct tm *current_time = localtime(&raw_time);

//     // current_time->tm_hour = new_time.tm_hour;
//     // current_time->tm_min = new_time.tm_min;
//     // current_time->tm_sec = new_time.tm_sec;
//     // current_time->tm_year = new_time.tm_year;
//     // current_time->tm_mon = new_time.tm_mon;
//     // current_time->tm_mday = new_time.tm_mday;

//     // time_t adjusted_time = mktime(current_time);

//     // if (adjusted_time != (time_t)-1)
//     // {

//     // system_time.wYear = (current_time->tm_year + 1900),
//     // system_time.wMonth = current_time->tm_mon + 1,
//     // system_time.wDayOfWeek = current_time->tm_wday,
//     // system_time.wDay = current_time->tm_mday,
//     // system_time.wHour = current_time->tm_hour,
//     // system_time.wMinute = current_time->tm_min,
//     // system_time.wSecond = current_time->tm_sec,
//     // system_time.wMilliseconds = 0;

//     SYSTEMTIME system_time;
//     GetLocalTime(&system_time);

//     system_time.wYear = tm_time.tm_year + 1900;
//     system_time.wMonth = tm_time.tm_mon + 1;
//     system_time.wDay = tm_time.tm_mday;
//     system_time.wHour = tm_time.tm_hour;
//     system_time.wMinute = tm_time.tm_min;
//     system_time.wSecond = tm_time.tm_sec;
//     system_time.wMilliseconds = 0;

//     if (!SetSystemTime(&system_time))
//     {
//         fprintf(stderr, "Error setting system time: %lu\n", GetLastError());
//     }
// #endif
// }

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         printf("Uso: time_setup <tempo>\n");
//         printf("Exemplo: time_setup 2023-07-24 12:34:56\n");
//         return 1;
//     }

//     const char *time_str = argv[1];

//     set_system_time(time_str);

// #ifdef _WIN32
//     system("pause");

// #endif

//     return 0;
// }

#include <stdio.h>
#include <Windows.h>

int main()
{
    SYSTEMTIME st;

    GetSystemTime(&st);

    printf("A hora é : %02d:%02d:%02d\n", st.wHour, st.wMinute, st.wSecond);

    int hora, minuto, dia, mes, ano;
    printf("Defina uma nova : \n");

    if (scanf("%d %d", &hora, &minuto) != 2)
    {
        printf("Defina uma nova hora: \n");
        // scanf("%d %d", &hora, &minuto);
        return -1;
    }

    if (scanf("%d %d", &dia, &mes, &ano) != 3)
    {
        printf("Defina uma nova dia");
        // scanf("%d %d", &dia, &mes, &ano);
        return 1;
    }
    
    st.wHour = hora;
    st.wMinute = minuto;
    st.wSecond = 0;

    st.wDay = dia;
    st.wMonth = mes;
    st.wYear = ano;

    return 0;
}



// #include <stdio.h>
// #include <time.h>
// #include <windows.h>

// void printCurrentSystemDateTime() {
//     SYSTEMTIME currentTime;
//     GetSystemTime(&currentTime);  // Get current system time

//     printf("Current system date and time: %04d-%02d-%02d %02d:%02d:%02d\n", 
//            currentTime.wYear, 
//            currentTime.wMonth, 
//            currentTime.wDay, 
//            currentTime.wHour, 
//            currentTime.wMinute, 
//            currentTime.wSecond);
// }

// void setSystemDateTime(int year, int month, int day, int hour, int minute, int second) {
//     SYSTEMTIME newTime;
//     GetSystemTime(&newTime);  // Get current system time

//     newTime.wYear = (WORD) year;
//     newTime.wMonth = (WORD) month;
//     newTime.wDay = (WORD) day;
//     newTime.wHour = (WORD) hour;
//     newTime.wMinute = (WORD) minute;
//     newTime.wSecond = (WORD) second;
//     newTime.wMilliseconds = 0;

//     // Ajustar a data e a hora usando SetSystemTime
//     if (SetSystemTime(&newTime)) {
//         printf("Data e hora do sistema definidas com sucesso.\n");
//     } else {
//         // Lidar com o erro quando SetSystemTime falhar
//         DWORD error = GetLastError();
//         LPSTR errorMessage = NULL;

//         // Obter a mensagem de erro correspondente ao código de erro
//         FormatMessageA(
//             FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//             NULL,
//             error,
//             MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//             (LPSTR)&errorMessage,
//             0,
//             NULL
//         );

//         printf("Falha ao definir a data e a hora do sistema. Código de erro: %ld\n", error);
//         if (errorMessage) {
//             printf("Mensagem de erro: %s\n", errorMessage);
//             // Liberar a memória alocada por FormatMessageA
//             LocalFree(errorMessage);
//         }
//     }
// }

// int main() {
//     printCurrentSystemDateTime();

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

//     return 0;
// }
#include <stdio.h>
#include <time.h>
#include <windows.h>

void printCurrentSystemDateTime() {
    SYSTEMTIME currentTime;
    GetSystemTime(&currentTime);  // Get current system time

    printf("Current system date and time: %04d-%02d-%02d %02d:%02d:%02d\n", 
           currentTime.wYear, 
           currentTime.wMonth, 
           currentTime.wDay, 
           currentTime.wHour, 
           currentTime.wMinute, 
           currentTime.wSecond);
}

void setSystemDateTime(int year, int month, int day, int hour, int minute, int second) {
    SYSTEMTIME newTime;
    GetSystemTime(&newTime);  // Get current system time

    newTime.wYear = (WORD) year;
    newTime.wMonth = (WORD) month;
    newTime.wDay = (WORD) day;
    newTime.wHour = (WORD) hour;
    newTime.wMinute = (WORD) minute;
    newTime.wSecond = (WORD) second;
    newTime.wMilliseconds = 0;

    // Ajustar a data e a hora usando SetSystemTime
    if (SetSystemTime(&newTime)) {
        printf("Data e hora do sistema definidas com sucesso.\n");
    } else {
        // Lidar com o erro quando SetSystemTime falhar
        DWORD error = GetLastError();
        LPSTR errorMessage = NULL;

        // Obter a mensagem de erro correspondente ao código de erro
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&errorMessage,
            0,
            NULL
        );

        printf("Falha ao definir a data e a hora do sistema. Código de erro: %ld\n", error);
        if (errorMessage) {
            printf("Mensagem de erro: %s\n", errorMessage);
            // Liberar a memória alocada por FormatMessageA
            LocalFree(errorMessage);
        }
    }
}

int main() {
    printCurrentSystemDateTime();

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




#ifndef TIME_SETUP_H
#define TIME_SETUP_H

void printCurrentSystemDateTime();
void setSystemDateTime(int year, int month, int day, int hour, int minute, int second);

#endif
