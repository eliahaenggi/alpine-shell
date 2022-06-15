#include "logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

FILE *file;
char fileLocation [PATH_MAX + FILENAME_MAX];

/**
 * createLog creates a empty log file
 */
void createLog() {
    deleteLog();
    file = fopen (fileLocation, "w");
    fclose(file);
}
/**
 * deletes the old log file
 */
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
/**
 * adds the specified string to the log
 * @param message the message, which should be added to the log
 */
void appendToLog(char message []){
    file = fopen(fileLocation, "a");
    fputs(message, file);
    fclose(file);
}

/**
 * prints the content of the log file on the console
 * @return 0 if successful
 */
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
    return 0;
}