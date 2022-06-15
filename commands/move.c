#include "move.h"
#include "directory.h"
#include "number_interface.h"
#include "../logger.h"

#include <string.h>
#include <stdio.h>
#include <limits.h>


/**
 * Moves a file according to the user input in chooseNum().
 *
 * @return 0 if file move was successful, not 0 if failed
 */

int moveFile() {
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
    char oldPath [PATH_MAX + FILENAME_MAX];
    strcpy(oldPath, path_origin);
    strcat(oldPath, "/");
    strcat(oldPath,file_name);
    char newPath [PATH_MAX + FILENAME_MAX];
    strcpy(newPath, destination);
    strcat(newPath, "/");
    strcat(newPath,file_name);
    appendToLog("move ");
    appendToLog(oldPath);
    appendToLog(" ");
    appendToLog(newPath);
    appendToLog(" ");
    int res = rename(oldPath, newPath);
    return res;
}