#include "../include/network_clock.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>

void printCurrentSystemDateTime()
{
    SYSTEMTIME currentTime;
    GetSystemTime(&currentTime); // Get current system time

    printf("Current system date and time: %04d-%02d-%02d %02d:%02d:%02d\n", // <-----------------------------------------
           currentTime.wYear,
           currentTime.wMonth,
           currentTime.wDay,
           currentTime.wHour,
           currentTime.wMinute,
           currentTime.wSecond);
}

void setSystemDateTime(int year, int month, int day, int hour, int minute, int second)
{ // <-----------------------------------------
    SYSTEMTIME newTime;
    GetSystemTime(&newTime); // Get current system time

    newTime.wYear = (WORD)year;
    newTime.wMonth = (WORD)month;
    newTime.wDay = (WORD)day;
    newTime.wHour = (WORD)hour;
    newTime.wMinute = (WORD)minute;
    newTime.wSecond = (WORD)second;
    newTime.wMilliseconds = 0;

    // Ajustar a data e a hora usando SetSystemTime
    if (SetSystemTime(&newTime))
    {
        printf("Data e hora do sistema definidas com sucesso.\n");
    }
    else
    {
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
            NULL);

        printf("Falha ao definir a data e a hora do sistema. Código de erro: %ld\n", error);
        if (errorMessage)
        {
            printf("Mensagem de erro: %s\n", errorMessage);
            LocalFree(errorMessage);
        }
    }
}

void getSystemDateTime(char *buffer)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void getSystemDateTimeInFormat(char *buffer, const char *format)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, format, timeinfo);
}
