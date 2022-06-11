#include "delete.h"
#include "rename.h"

/**
 * Deletes file with specified name. Returns 0 if deleting was successful. Uses setOldFileName function from rename.c.
 */
int deleteFile(char* name) {
    int res = setOldFileName(name);
    if (res == -1) {
        return -1;
    }
    res = remove(old_filename);
    return res;
}