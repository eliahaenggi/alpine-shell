#include "executor.h"
#include "parser.h"
#include "commands/rename.h"
#include "commands/delete.h"
#include <stdio.h>

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
            break;
        case directory:
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