#include "logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

FILE *file;
char fileLocation [PATH_MAX + FILENAME_MAX];

void createLog() {
    deleteLog();
    file = fopen (fileLocation, "w");
    fclose(file);
}

void deleteLog() {
    getcwd(fileLocation, PATH_MAX);
    strcat(fileLocation, "/log.txt");
    FILE* file;
    file = fopen(fileLocation, "r");
    if (!file) {
        return;
    } else {
        fclose(file);
    }
    remove(fileLocation);
}
void appendToLog(char message []){
    file = fopen(fileLocation, "a");
    fputs(message, file);
    fclose(file);
}

int printLog() {
    file = fopen(fileLocation, "r");
    int i;
    while (1) {
        i = fgetc(file);
        if (i == EOF) {
            break;
        }
        printf("%c", i);
    }
    fclose(file);
}