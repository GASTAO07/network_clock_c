// #include "../include/config.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ShlObj.h>
// #include <Windows.h>

// #ifdef _WIN32

// WCHAR *get_config_file_path() // change from char* to WCHAR*
// {
//     char appDataPath[MAX_PATH];
//     WCHAR *config_file_path = NULL;

//     if(GetEnvironmentVariableA("LOCALAPPDATA", appDataPath, MAX_PATH) == 0){
//         fprintf(stderr, "Error getting AppData path ùlu\n", GetLastError());
//         return NULL; 
//     }

//     int length = MultiByteToWideChar(CP_ACP, 0, appDataPath, -1, NULL, 0);
//     config_file_path = (WCHAR *)malloc(length * sizeof(WCHAR));
//     if(config_file_path)
//     {
//         MultiByteToWideChar(CP_ACP, 0, appDataPath, -1, config_file_path, length);
//         wcscat(config_file_path, L"\\Clock\\port.txt");
//         return config_file_path;
//     }
//     else
//     {
//         fprintf(stderr, "Error allocating memory for config file \n");
//         return NULL;
//     }
// }

// #endif


// WCHAR *get_config_file_path_with_name(){
//     return get_config_file_path();
// }



#include "../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ShlObj.h>
#include <Windows.h>
#include <wchar.h>

#ifdef _WIN32
int read_port_from_config() {
    WCHAR *config_file_path = get_config_file_path();
    if (config_file_path == NULL) {
        fprintf(stderr, "Error getting file path.\n");
        return -1;
    }

    // Debug print: Print the file path to check if it's correct
    wprintf(L"Config file path: %s\n", config_file_path);

    // Open the file using Windows API
    HANDLE hFile = CreateFileW(config_file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    free(config_file_path);
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening config file.\n");
        return -1;
    }

    char buffer[64]; // Assuming the port number will not exceed 63 characters
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        fprintf(stderr, "Error reading from config file.\n");
        CloseHandle(hFile);
        return -1;
    }

    // Null-terminate the buffer
    buffer[(int)bytesRead] = '\0';

    // Close the file handle
    CloseHandle(hFile);

    // Convert the buffer to an integer and return the port number
    int port = atoi(buffer);
    return port;
}
WCHAR *get_config_file_path()
{
    WCHAR appDataPath[MAX_PATH];
    WCHAR config_file_path[MAX_PATH]; // Update to use a buffer for the file path

    if (GetEnvironmentVariableW(L"LOCALAPPDATA", appDataPath, MAX_PATH) == 0) {
        fprintf(stderr, "Error getting AppData path.\n");
        return NULL;
    }

    wsprintfW(config_file_path, L"%s\\Clock\\port.txt", appDataPath);

    // Debug print: Print the complete file path to check if it's correct
    wprintf(L"Complete file path: %ls\n", config_file_path);

    return wcsdup(config_file_path); // Return a duplicate of the file path
}

#endif

WCHAR *get_config_file_path_with_name() {
    return get_config_file_path();
}

// int main() {
//     int port = read_port_from_config();
//     if (port == -1) {
//         printf("Failed to read the port from the configuration file.\n");
//         return 1;
//     }

//     printf("Port number read from config file: %d\n", port);
//     return 0;
// }
