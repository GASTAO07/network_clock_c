#ifndef SECURITY_H
#define SECURITY_H

#ifdef _WIN32
#define WINVER 0x0600 

#include <Windows.h>
#include <AccCtrl.h>
#include <AclAPI.h>
#include <Sddl.h>
#include <ShlObj.h>
#include <stdio.h>
#endif

#ifndef FOLDERID_LocalAppData
extern const GUID FOLDERID_LocalAppData;
#endif

#ifdef _WIN32
int check_and_set_config_file_permissions();
#endif

#endif
