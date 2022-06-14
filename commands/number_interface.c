#include "number_interface.h"
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
 * Return -2, if filesAndDirectories is NULL
 */
int choose_file(int number){
    if (files->next != NULL){
        struct names_node *temp = files;
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

/**
 * Return -1, if number is not inside directory (e.g. accessing 100th file in directory with 2)
 * Return 0, if it succeeds
 * Return -2, if filesAndDirectories is NULL
 */
int choose_destination(int number){
    if (directories != NULL){
        struct names_node *temp = directories;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->number==number){
                chdir(temp->name);
                getcwd(cwd, PATH_MAX);
                strcpy(destination, cwd);
                return 0;
            }
        } return -1;
    } else {
        printf("WTF HAPPENED?");
        return -2;
    }
}

/**
 * Takes the input of the user. Checks if input is number.
 *
 * @return Number entered by the user
 */
int chooseNum() {
    printPrompt2();
    char *command = readCommand();
    if (strcmp(command, "exit\n") == 0) {
        free(command);
        return -1;
    }
    if (strcmp(command, "\n") == 0) {
        free(command);
        return -2;
    }
    command[strlen(command)-1] = '\0'; // cut of \n at the end of command to convert it to int
    if (!isNumber(command)) {
        printf("Input should be a number.\n");
        return -1;
    }
    int num = atoi(command);
    free(command);
    printf("Selected Number: %d\n", num);
    return num;
}

/**
 * Checks if input string is a number. Used to convert string to int afterwards.
 */
int isNumber(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}