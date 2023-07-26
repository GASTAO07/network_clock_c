// #ifndef CONFIG_H
// #define CONFIG_H

// WCHAR *get_config_file_path(); 
// // char *get_config_file_path_with_name(); 

// #endif

#ifndef CONFIG_H
#define CONFIG_H
#include <windows.h>

WCHAR *get_config_file_path(); // changed from char* to WCHAR*
WCHAR *get_config_file_path_with_name(); 

#endif
