#include "move.h"
#include "directory.h"
#include "../shell.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int choose_file(int number){
    DIR* dir = getcwd(cwd, PATH_MAX);
}

int moveFile();

int chooseNum() {
    while (1) {
        show_content();
        printPrompt2();
        char *command = readCommand();
        if (strcmp(command, "exit\n") == 0) {
            free(command);
            return 0;
        }
        if (strcmp(command, "\n") == 0) {
            //moveFile();
            printf("File should be moved now.\n");
            free(command);
            return 0;
        }
        command[strlen(command)-1] = '\0'; // cut of \n at the end of command to convert it to int
        if (!isNumber(command)) {
            printf("Input should be a number.\n");
            return -1;
        }
        int num = atoi(command);
        free(command);
        printf("Directory should be changed now: %d\n", num);
        //choose_file(num);
    }

}

int isNumber(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}