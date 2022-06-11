#include "rename.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>


/**
 * Checks if file with specified name exists and sets global variable old_filename to name. Returns -1 if file does not exist.
 */
int setOldFileName(char* name) {
    FILE* file;
    file = fopen(name, "r");
    if (!file) {
        printf("File does not exist. ");
        return -1;
    } else {
        fclose(file);
    }
    strcpy(old_filename, name);
    return 0;
}

int renameFile(char* oldName, char* newName) {
    setOldFileName(oldName);
    int res = rename(old_filename, newName);
    return res;
}
