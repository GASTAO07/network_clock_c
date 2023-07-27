#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32

#include <windows.h>

WCHAR *get_config_file_path();
WCHAR *get_config_file_path_with_name();
#endif

int read_port_from_config();

#endif
