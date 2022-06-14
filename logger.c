//
// Created by Matthew on 14/06/2022.
//

#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

FILE *file;
char fileLocation [PATH_MAX + FILENAME_MAX];

void createLog(){
    deleteLog();
    file = fopen (fileLocation, "w");
    fclose(file);
}

void deleteLog(){
    getcwd(fileLocation, PATH_MAX);
    strcat(fileLocation, "/log.txt");
    remove(fileLocation);
}
void appendToLog(char message []){
    file = fopen(fileLocation, "w");
    fputs(message, file);
    fclose(file);
}