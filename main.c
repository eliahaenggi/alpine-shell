#include "shell.h"
#include "reader.h"
#include "tokenizer.h"
#include "reader.h"
#include "parser.h"
#include "commands/directory.h"
#include "executor.h"
#include "commands/rename.h"
#include "commands/move.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/**
 * starts the whole shell
 * @return 0 if successful
 */
int start(int argc, char **argv) {
    createLog();
    char *cmd;
    while (1) {
        printPrompt1();
        cmd = readCommand();
        if (cmd[0] == '\0') {
            free(cmd);
            continue;
        }
        if (strcmp(cmd, "exit\n") == 0) {
            free(cmd);
            break;
        }
        if (strcmp(cmd, "\n") == 0) {
            free(cmd);
            continue;
        }
        reader reader;
        reader.cmd = cmd;
        reader.cmdLength = strlen(cmd);
        reader.index = -1;
        execute(&reader);
        free(cmd);
    }
    return 0;
}
/**
 * reads the input of the user
 * @return the input of the user as string
 */
char* readCommand() {
    char buffer[512];
    char *ptr = NULL;
    char ptrLength = 0;

    while (fgets(buffer, 512, stdin)) {
        int bufferLength = strlen(buffer);

        if (!ptr) {
            ptr = malloc(bufferLength);
        } else {
            char* newptr = malloc(ptrLength + bufferLength);
            ptr = newptr;
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

    if (tok == &EOFToken) {
        return 0;
    }
    cmd *command = createCommand();
    while (tok != &EOFToken) {
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

int printPrompt1() {
    char cwdir [PATH_MAX];
    getcwd(cwdir, PATH_MAX);
    fprintf(stderr, "%s$ ", cwdir);
    return 0;
}

int printPrompt2() {
    fprintf(stderr, "> ");
    return 0;
}

int main(int argc, char **argv) {
    start(argc, argv);
}
