// time.h
#ifndef TIME_H
#define TIME_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#endif

// Function declarations for setting and getting system date and time

#ifdef _WIN32
void setSystemDateTime(int year, int month, int day, int hour, int minute, int second);
#else
int setSystemDateTime(int year, int month, int day, int hour, int minute, int second);
#endif

#ifdef _WIN32
void getSystemDateTime(int *year, int *month, int *day, int *hour, int *minute, int *second);
#else
int getSystemDateTime(int *year, int *month, int *day, int *hour, int *minute, int *second);
#endif

#endif // TIME_H