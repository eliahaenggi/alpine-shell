
#include "move.h"
#include "directory.h"
#include "../shell.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char path_origin [PATH_MAX];
char destination [PATH_MAX];
char file_name [FILENAME_MAX];

/**
 * Return -1, if number is not inside directory (e.g. accessing 100th file in directory with 2)
 * Return 0, if it succeeds
 * Return -2, if current_files is NULL
 */
int choose_file(int number){
    if (current_files != NULL){
        struct names_node *temp = current_files;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->number==number){
                strcpy(file_name, temp->name);
                strcpy(path_origin, cwd);
                return 0;
            }
        } return -1;
    } else {
        printf("WTF HAPPENED?");
        return -2;
    }
}

int choose_destination(int number){
    if (current_files != NULL){
        struct names_node *temp = current_files;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->number==number){
                strcpy(destination, getcwd(cwd, PATH_MAX));
                return 0;
            }
        } return -1;
    } else {
        printf("WTF HAPPENED?");
        return -2;
    }
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