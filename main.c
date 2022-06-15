#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include "reader.h"
#include "tokenizer.h"
#include "reader.h"
#include "parser.h"
#include "commands/directory.h"
#include "executor.h"
#include "commands/rename.h"
#include "commands/move.h"


int start(int argc, char **argv) {
    char *cmd;
    while (1) {
        printPrompt1();
        cmd = readCommand();
        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0) {
            free(cmd);
            continue;
        }
        if (strcmp(cmd, "exit\n") == 0) {
            free(cmd);
            break;
        }
        reader reader;
        reader.cmd = cmd;
        reader.cmdLength = strlen(cmd);
        reader.index = -1;
        execute(&reader);
        free(cmd);
    }
    exit(EXIT_SUCCESS);
}

char* readCommand() {
    char buffer[512];
    char *ptr = NULL;
    char ptrLength = 0;

    while (fgets(buffer, 512, stdin)) {
        int bufferLength = strlen(buffer);
        if (!ptr) {
            ptr = malloc(bufferLength + 1);
        } else {
            char *ptr2 = realloc(ptr, ptrLength + bufferLength + 1);
            if (ptr2) {
                ptr = ptr2;
            } else {
                free(ptr);
                ptr = NULL;
            }
        }
        strcpy(ptr + ptrLength, buffer);
        if (buffer[bufferLength - 1] == '\n') {
            return ptr;
        }
        ptrLength = ptrLength + bufferLength;
    }
    return ptr;
}

int execute(reader* reader) {
    skipWhiteSpaces(reader);

    token *tok = tokenize(reader);

    if (tok == &eof_token) {
        return 0;
    }
    cmd *command = createCommand();
    while (tok && tok != &eof_token) {
        node *n = createNode(tok);
        addNodeToList(n, command);
        if (command->length == 1) {
            setCmdType(command);
        }
        tok = tokenize(reader);
    }
    executeCmd(command);
    freeCommand(command);
    return 0;
}

void printPrompt1() {
    char cwdir [PATH_MAX];
    getcwd(cwdir, PATH_MAX);
    fprintf(stderr, "%s$ ", cwdir);
}

void printPrompt2() {
    fprintf(stderr, "> ");
}

int main(int argc, char **argv) {
    start(argc, argv);
}
