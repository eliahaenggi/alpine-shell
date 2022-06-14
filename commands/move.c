#include "move.h"
#include "directory.h"
#include "number_interface.h"
#include <string.h>
#include <stdio.h>
#include "../logger.h"


/**
 * Moves a file according to the user input in chooseNum().
 *
 * @return 0 if file move was successful, not 0 if failed
 */

int moveFile() {
    show_files_();
    int num = chooseNum();
    if (num == -1 || num == -2) { // exit move command or wrong input
        return -1;
    }
    choose_file(num);
    while (1) {
        show_directories();
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
    printf("OldPath: %s\n", oldPath);
    printf("NewPath: %s\n", newPath);
    appendToLog("The file:");
    appendToLog(file_name);
    appendToLog(" was moved from: ");
    appendToLog(oldPath);
    appendToLog(" to: ");
    appendToLog(newPath);
    appendToLog("\n");
    int res = rename(oldPath, newPath);
    return res;
}