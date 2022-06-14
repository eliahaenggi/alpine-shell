#include "delete.h"
#include "rename.h"
#include <stdio.h>
#include <string.h>
#include "directory.h"
#include "number_interface.h"

/**
 * Deletes file with specified name. Returns 0 if deleting was successful. Uses setOldFileName function from rename.c.
 */
int deleteFile(char* name) {
    FILE* file;
    file = fopen(name, "r");
    if (!file) {
        printf("File does not exist. ");
        return -1;
    } else {
        fclose(file);
    }
    int res = remove(name);
    return res;
}

int chooseDeleteFile() {
    show_files_(1);
    int num = chooseNum();
    if (num == -1 || num == -2) { // exit move command or wrong input
        return -1;
    }
    choose_file(num);
    char oldPath [strlen(path_origin)];
    strcpy(oldPath, path_origin);
    strcat(oldPath, "/");
    strcat(oldPath,file_name);
    int res = deleteFile(oldPath);
    return res;
}