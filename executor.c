#include "executor.h"
#include "parser.h"
#include "commands/rename.h"
#include "commands/delete.h"
#include <stdio.h>
#include "commands/directory.h"
#include "commands/move.h"
#include "commands/copy.h"
#include "commands/number_interface.h"
#include <stdlib.h>
#include <string.h>
#include "commands/help.h"


/**
 * Executes a command parsed by the parser. Uses the set cmdType enum the differentiate between commands. If commands
 * has error-enum, the input of the user is unknown. Print statements after the commands execution are handled here.
 *
 * @param command Command to be executed.
 */
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
            } else if (command->length == 3) {
                res = copyFiles(command->head->next->tok.text, command->head->next->next->tok.text);
                if (res != 0) {
                    printf("File could not be copied.\n");
                    return;
                }
            } else {
                printf("Invalid number of arguments for copy.\n");
                return;
            }
            break;
        case directory:
            show_content();
            break;
        case show_files:
            show_files_(0);
            break;
        case show_dir:
            show_directories(0);
            break;
        case go:
            if (command->length == 1) {
                printf("Which directory would you like to access?\n");
                show_directories(1);
                change_directory(chooseNum());
            } else {
                printf("Invalid number of arguments for go.\n");
                return;
            }
            break;
        case run:
            if(command->length < 2) {
                printf("Correct command usage: \" run <filename>\"");
            } else {
                char rest [PATH_MAX];
                memset(rest,0, strlen(rest));
                node *temp = command->head;
                while (temp->next!=NULL) {
                    temp=temp->next;
                    strcat(rest, temp->tok.text);
                    strcat(rest, " ");
                }
                rest[strlen(rest)-1] = '\0';
                system(rest);
            }
            break;
        case help:
            printHelp();
            break;
        case error:
            printf("Command is not known.\n");
            break;
    };
}