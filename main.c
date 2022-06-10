#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include "reader.h"
#include "tokenizer.h"
#include "reader.h"

int main(int argc, char **argv) {
    char *cmd;
    while (1) {
        printPrompt1();
        cmd = readCommand();
        if (!cmd) {
            exit(EXIT_SUCCESS);
        }
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
    char buffer[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while(fgets(buffer, 1024, stdin)) {
        int buflen = strlen(buffer);
        if (!ptr) {
            ptr = malloc(buflen+1);
        } else {
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);
            if(ptr2) {
                ptr = ptr2;
            } else {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr) {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr+ptrlen, buffer);

        if (buffer[buflen-1] == '\n') {
            if (buflen == 1 || buffer[buflen-2] != '\\') {
                return ptr;
            }
            ptr[ptrlen+buflen-2] = '\0';
            buflen = buflen - 2;
            printPrompt2();
        }
        ptrlen = ptrlen + buflen;
    }

    return ptr;
}

int execute(reader *reader) {
    skipWhiteSpaces(reader);

    struct token *tok = tokenize(reader);

    if (tok == &eof_token) {
        return 0;
    }
    //printf("Whole cmd:\n%s", reader->cmd);
    //printf("Tokens:\n");
    while (tok && tok != &eof_token) {
        // TODO: Execute command
        //printf("%s|", tok->text);
        tok = tokenize(reader);
    }
    return 0;
}

void printPrompt1() {
    fprintf(stderr, "$ ");
}

void printPrompt2() {
    fprintf(stderr, "> ");
}