#include "executor.h"
#include "parser.h"
#include "commands/rename.h"
#include "commands/delete.h"
#include <stdio.h>
#include "commands/directory.h"
#include "commands/move.h"
#include "commands/copy.h"

void executeCmd(cmd* command) {
    int res = 0; // 0 if command executed as expected. Else if execution failed.
    switch(command->type) {
        case delete:
            if (command->length != 2) {
                printf("Invalid number of arguments for delete.\n");
                return;
            }
            res = deleteFile(command->head->next->tok.text); // call second node of command linked list
            if (res == 0) {
                printf("File deleted successfully.\n");
            } else {
                printf("Delete failed.\n");
            }
            break;
        case move:
            if (command->length == 1) {
                res = moveFile();
                if (res != 0) {
                    printf("File could not be moved.\n");
                    return;
                }
                printf("Moved file successfully.\n");
            } else if (command->length == 3) {
                res = renameFile(command->head->next->tok.text, command->head->next->next->tok.text); // call second and third node of command linked list
                if (res == 0) {
                    printf("File moved successfully.\n");
                } else {
                    printf("File could not be moved.\n");
                }
            } else {
                printf("Invalid number of arguments for move.\n");
                return;
            }
            break;
        case re_name:
            if (command->length != 3) {
                printf("Invalid number of arguments for rename.\n");
                return;
            }
            res = renameFile(command->head->next->tok.text, command->head->next->next->tok.text); // call second and third node of command linked list
            if (res == 0) {
                printf("File renamed successfully.\n");
            } else {
                printf("Rename failed.\n");
            }
            break;
        case copy:
            if (command->length == 1) {
                res = copyFile();
                if (res != 0) {
                    printf("File could not be copied.\n");
                    return;
                }
                printf("Copied file successfully.\n");
            } else {
                printf("Invalid number of arguments for copy.\n");
                return;
            }
            break;
        case directory:
            show_content();
            break;
        case show_files:
            break;
        case show_dir:
            break;
        case error:
            printf("Command is not known.\n");
            break;
    };
}