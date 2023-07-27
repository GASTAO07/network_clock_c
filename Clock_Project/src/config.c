#include "../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ShlObj.h>
#include <Windows.h>
#include <wchar.h>

#ifdef _WIN32
int read_port_from_config()
{
    WCHAR *config_file_path = get_config_file_path();
    if (config_file_path == NULL)
    {
        fprintf(stderr, "Error getting file path.\n");
        return -1;
    }

    wprintf(L"Config file path: %s\n", config_file_path);

    HANDLE hFile = CreateFileW(config_file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    free(config_file_path);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening config file.\n");
        return -1;
    }

    char buffer[64];// <-----------------------------------------
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
    {
        fprintf(stderr, "Error reading from config file.\n");
        CloseHandle(hFile);
        return -1;
    }

    buffer[(int)bytesRead] = '\0';

    CloseHandle(hFile);
    int port = atoi(buffer);
    return port;
}
WCHAR *get_config_file_path()
{
    WCHAR appDataPath[MAX_PATH];
    WCHAR config_file_path[MAX_PATH];
    if (GetEnvironmentVariableW(L"LOCALAPPDATA", appDataPath, MAX_PATH) == 0)
    {
        fprintf(stderr, "Error getting AppData path.\n");
        return NULL;
    }

    wsprintfW(config_file_path, L"%s\\Clock\\port.txt", appDataPath);
    wprintf(L"Complete file path: %ls\n", config_file_path);

    return wcsdup(config_file_path);
}

#endif

WCHAR *get_config_file_path_with_name()
{
    return get_config_file_path();
}
