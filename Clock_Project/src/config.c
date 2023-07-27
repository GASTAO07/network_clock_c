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
// }#include "../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ShlObj.h>
#include <Windows.h>

#ifdef _WIN32

WCHAR *get_config_file_path() // change from char* to WCHAR*
{
    char appDataPath[MAX_PATH];
    WCHAR *config_file_path = NULL;

    if(GetEnvironmentVariableA("LOCALAPPDATA", appDataPath, MAX_PATH) == 0){
        fprintf(stderr, "Error getting AppData path ùlu\n", GetLastError());
        return NULL; 
    }

    int length = MultiByteToWideChar(CP_ACP, 0, appDataPath, -1, NULL, 0);
    config_file_path = (WCHAR *)malloc(length * sizeof(WCHAR));
    if(config_file_path)
    {
        MultiByteToWideChar(CP_ACP, 0, appDataPath, -1, config_file_path, length);
        wcscat(config_file_path, L"\\Clock\\port.txt");
        return config_file_path;
    }
    else
    {
        fprintf(stderr, "Error allocating memory for config file \n");
        return NULL;
    }
}

#endif

WCHAR *get_config_file_path_with_name(){
    return get_config_file_path();
}
