#include "copy.h"
#include "number_interface.h"
#include "directory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**opy
 * Copies a file according to the user input in chooseNum(). Uses copyFiles().
 *
 * @return 0 if file copy was successful, not 0 if failed
 */
int copyFile() {
    show_files_(1);
    int num = chooseNum();
    if (num == -1 || num == -2) { // exit move command or wrong input
        return -1;
    }
    choose_file(num);
    while (1) {
        show_directories(1);
        num = chooseNum();
        if (num == -1) { // exit move command or wrong input
            return -1;
        }
        if (num == -2) { // Enter typed
            break;
        }
        choose_destination(num);
    }
    char oldPath [strlen(path_origin)];
    strcpy(oldPath, path_origin);
    strcat(oldPath, "/");
    strcat(oldPath,file_name);
    char newPath [strlen(destination)];
    strcpy(newPath, destination);
    strcat(newPath, "/");
    strcat(newPath,file_name);
    int res = copyFiles(oldPath, newPath);
    return res;
}


/**
 * Reads the informaton in source_file and writes them into the specified address of copied_file.
 *
 * @param source_file path of file to copy
 * @param copied_file path of copied file
 * @return 0 if copy was successful.
 */
int copyFiles(char* source_file, char* copied_file) {
    char data;
    FILE* source = fopen(source_file, "r");
    if (!source) {
        exit(EXIT_FAILURE);
    }

    FILE* copy = fopen(copied_file, "w");
    if (!copy) {
        fclose(source);
        exit(EXIT_FAILURE);
    }
    while(1) {
        data = fgetc(source);
        if (data == EOF) {
            break;
        }
        fputc(data, copy);
    }
    fclose(source);
    fclose(copy);
}