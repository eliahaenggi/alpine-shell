//
// Created by Matthew on 14/06/2022.
//

#ifndef CLASSIC_C_LOGGER_H
#define CLASSIC_C_LOGGER_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

extern FILE *file;
extern char fileLocation [PATH_MAX + FILENAME_MAX];

void createLog();
void deleteLog();
void appendToLog(char message []);

#endif //CLASSIC_C_LOGGER_H
