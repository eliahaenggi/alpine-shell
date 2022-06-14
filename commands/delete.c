#include "delete.h"
#include "rename.h"
#include <stdio.h>

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