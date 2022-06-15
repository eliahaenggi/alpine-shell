#include "executor.h"
#include "parser.h"
#include "commands/rename.h"
#include "commands/delete.h"
#include "commands/directory.h"
#include "commands/move.h"
#include "commands/copy.h"
#include "commands/number_interface.h"
#include "commands/help.h"
#include "logger.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * Executes a command parsed by the parser. Uses the set cmdType enum the differentiate between commands. If commands
 * has error-enum, the input of the user is unknown. Print statements after the commands execution are handled here.
 *
 * @param command Command to be executed.
 */
void executeCmd(cmd* command) {
    int res = 0; // 0 if command executed as expected. Else if execution failed.
    int numReq = 0; // 1 if command required selection of file or dir by entering integer
    switch(command->type) {
        case delete:
            if (command->length == 2) {
                res = deleteFile(command->head->next->tok.text); // call second node of command linked list
                appendToLog(command->head->next->tok.text);
                if (res != 0) {
                    break;
                }
            } else if (command->length == 1) {
                numReq = 1;
                res = chooseDeleteFile();
                if (res != 0) {
                    printf("\033[1;31mDelete failed.\033[0m\n");
                }
            } else {
                printf("\033[1;31mInvalid number of arguments for delete.\033[0m\n");
                break;
            }
            break;
        case move:
            if (command->length == 1) {
                numReq = 1;
                res = moveFile();
                if (res != 0) {
                    printf("\033[1;31mFile could not be moved.\033[0m\n");
                    break;
                }
            } else if (command->length == 3) {
                res = renameFile(command->head->next->tok.text, command->head->next->next->tok.text); // call second and third node of command linked list
                if (res != 0) {
                    printf("\033[1;31mFile could not be moved.\033[0m\n");
                }
            } else {
                printf("\033[1;31mInvalid number of arguments for move.\033[0m\n");
                res = -1;
                break;
            }
            break;
        case re_name:
            if (command->length != 3) {
                printf("\033[1;31mInvalid number of arguments for rename.\033[0m\n");
                res = -1;
                break;
            }
            res = renameFile(command->head->next->tok.text, command->head->next->next->tok.text); // call second and third node of command linked list
            if (res != 0) {
                printf("\033[1;31mRename failed.\033[0m\n");
            }
            break;
        case copy:
            if (command->length == 1) {
                numReq = 1;
                res = copyFile();
                if (res != 0) {
                    printf("\033[1;31mFile could not be copied.\033[0m\n");
                    break;
                }
            } else if (command->length == 3) {
                res = copyFiles(command->head->next->tok.text, command->head->next->next->tok.text);
                if (res != 0) {
                    printf("\033[1;31mFile could not be copied.\033[0m\n");
                    break;
                }
            } else {
                printf("\033[1;31mInvalid number of arguments for copy.\033[0m\n");
                res = -1;
                break;
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
                numReq = 1;
                show_directories(1);
                res = change_directory(chooseNum());
                if (res != 0) {
                    printf("\033[1;31mDirectory change failed.\033[0m\n");
                }
            } else {
                printf("\033[1;31mInvalid number of arguments for go.\033[0m\n");
                res = -1;
                break;
            }
            break;
        case run:
            if(command->length < 2) {
                printf("\033[1;31mInvalid number of arguments for run.\033[0m\n");
            } else {
                char rest [PATH_MAX];
                memset(rest,0, strlen(rest));
                node *temp = command->head;
                while (temp->next!=NULL) {
                    temp = temp->next;
                    strcat(rest, temp->tok.text);
                    strcat(rest, " ");
                }
                rest[strlen(rest)-1] = '\0';
                res = system(rest);
                if (res != 0) {
                    printf("\033[1;31mExecution of command failed.\033[0m\n");
                }
            }
            break;
        case help:
            printHelp();
            break;
        case log:
            printLog();
            break;
        case error:
            printf("\033[1;31mCommand is not known.\033[0m\n");
            res = -1;
            break;
    };
    // Append Command to Log
    if (!numReq) {
        node* n = command->head;
        while (n) {
            appendToLog(n->tok.text);
            appendToLog(" ");
            n = n->next;
        }
    }
    if (res != 0) {
        appendToLog("FAILED\n");
    } else {
        appendToLog("\n");
    }
};