#include "../include/security.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../include/config.h"
#include <time.h>


#ifdef _WIN32

#ifndef FOLDERID_LocalAppData
extern const GUID FOLDERID_LocalAppData;
#endif

int check_and_set_config_file_permissions()
{
    WCHAR *config_file_path = get_config_file_path();
    if (config_file_path == NULL)
    {
        fprintf(stderr, "Error getting file path.\n");
        return -1;
    }

    wprintf(L"Config file path: %s\n", config_file_path); // Print the file path

    HANDLE hFile = CreateFileW(config_file_path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    free(config_file_path);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening file %lu\n", GetLastError());
        return -1;
    }

    EXPLICIT_ACCESSW explicit_access[1];
    PACL acl = NULL;

    ZeroMemory(&explicit_access, sizeof(EXPLICIT_ACCESSW));
    explicit_access[0].grfAccessPermissions = GENERIC_READ | GENERIC_WRITE;
    explicit_access[0].grfAccessMode = SET_ACCESS;
    explicit_access[0].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    explicit_access[0].Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    explicit_access[0].Trustee.TrusteeType = TRUSTEE_IS_USER;
    explicit_access[0].Trustee.ptstrName = L"Users";

    DWORD result = SetEntriesInAclW(1, explicit_access, NULL, &acl);
    if (result != ERROR_SUCCESS)
    {
        CloseHandle(hFile);
        fprintf(stderr, "Error setting ACL %lu\n", result);
        return -1;
    }

    if (!SetSecurityInfo(hFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, acl, NULL))
    {
        CloseHandle(acl);
        CloseHandle(hFile);
        fprintf(stderr, "Error setting security %lu\n", GetLastError());
        return -1;
    }
    LocalFree(acl);
    CloseHandle(hFile);
    return 0;
}

#endif

// void handleErrors(void)
// {
//   ERR_print_errors_fp(stderr);
//   abort();
// }

// int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,

// }

// int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,

// }

// int main() {
// #ifdef _WIN32
//     // Test getting the AppData path
//     WCHAR *config_file_path = get_config_file_path();
//     if (config_file_path == NULL)
//     {
//         fprintf(stderr, "Error getting file path.\n");
//         return -1;
//     }

//     wprintf(L"AppData path: %s\n", config_file_path);
//     free(config_file_path);
// #endif

//     return 0;
// }