#ifndef LOGGER_H
#define LOGGER_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

extern FILE *file;
extern char fileLocation [PATH_MAX + FILENAME_MAX];

void createLog();
void deleteLog();
void appendToLog(char message []);
int printLog();
#endif