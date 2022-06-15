#include "rename.h"

#include <stdio.h>
#include <string.h>


/**
 * Checks if file with specified name exists and sets global variable old_filename to name. Returns -1 if file does not exist.
 * @param name the name of the file, which should be renamed
 * @return 0, if successful, -1 if file could not be found
 */
int setOldFileName(char *name) {
    FILE *file;
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

 /**
  * Renames file to specified new name. Returns 0 if renaming was successful.
  * @param oldName The name of the file which should be renamed
  * @param newName The new name of the file
  * @return 0, if successful
  */
int renameFile(char *oldName, char *newName) {
    int res = setOldFileName(oldName);
    if (res == -1) {
        return -1;
    }
    res = rename(old_filename, newName);
    return res;
}
