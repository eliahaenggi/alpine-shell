#ifndef NUMBER_INTERFACE_H
#define NUMBER_INTERFACE_H
#include <limits.h>
#include <stdio.h>

extern char path_origin [PATH_MAX];
extern char destination [PATH_MAX];
extern char file_name [FILENAME_MAX];

int choose_file(int number);
int choose_destination(int num);
int chooseNum();
int isNumber(char* input);
#endif
