#include "executor.h"
#include "parser.h"
#include "commands/rename.h"
#include <stdio.h>

void executeCmd(cmd* command) {
    switch(command->type) {
        case delete:
            break;
        case move:
            break;
        case re_name:
            if (command->length != 3) {
                printf("Invalid number of arguments for rename.\n");
                return;
            }
            int res = renameFile(command->head->next->tok.text, command->head->next->next->tok.text); // call second and third argument of command
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