#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ShlObj.h>
#include <Windows.h>


#ifdef _WIN32

char *get_config_file_path()
{
    char appDataPath[MAX_PATH];
    char *config_file_path = NULL;

    if(GetEnvironmentVariableA("LOCALAPPDATA", appDataPath, MAX_PATH) == 0){
        fprintf(stderr, "Error getting AppData path ùlu\n", GetLastError());
        return NULL; 
    }

    config_file_path = (char *)malloc(strlen(appDataPath)+14);
    if(config_file_path)
    {
        sprintf(config_file_path, "%s\\Clock\\port.txt", appDataPath);
        return config_file_path;
    }
    else
    {
        fprintf(stderr, "Error allocating memory for config file \n");
        return NULL;
    }
}

#endif

char *get_config_file_path_with_name(){
    return get_config_file_path();
}

// int main(){
//     char *config_path = get_config_file_path_with_name();
//     if(config_path){
//         printf("Config path:%s\n", config_path);
//         free(config_path);
//     }
//     return 0;
// }