#ifndef TIME_SETUP_H
#define TIME_SETUP_H

void printCurrentSystemDateTime();
void setSystemDateTime(int year, int month, int day, int hour, int minute, int second);
void getSystemDateTime(char* buffer);
void getSystemDateTimeInFormat(char *buffer, const char *format);
#endif
