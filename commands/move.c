
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
    printf("iaopsmdpamsdpmaspdmaspüldmapsdm\r\n");
    printf(cwd);
    struct names_node c = show_content();
    if (c.next != NULL){
        struct names_node *temp = &c;
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
    if (filesAndDirectories != NULL){
        struct names_node *temp = filesAndDirectories;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->number==number){
                chdir(temp->name);
                strcpy(destination, getcwd(cwd, PATH_MAX));
                return 0;
            }
        } return -1;
    } else {
        printf("WTF HAPPENED?");
        return -2;
    }
}

int moveFile() {
    show_content();
    int num = chooseNum();
    if (num == -1) { // exit move command
        return 0;
    }
    if (num == -3) { // Input not a number
        return -1;
    }
    choose_file(num);
    while (1) {
        int num = chooseNum();
        if (num == -1) { // exit move command
            return 0;
        }
        if (num == -2) { // Enter typed
            break;
        }
        if (num == -3) { // Input not a number
            return -1;
        }
        choose_destination(num);
    }
    char oldPath [strlen(path_origin) + strlen(file_name) + 1];
    strcpy(oldPath, path_origin);
    strcat(oldPath, "/");
    strcat(oldPath,file_name);
    char newPath [strlen(destination) + strlen(file_name) + 1];
    strcpy(oldPath, destination);
    strcat(oldPath, "/");
    strcat(oldPath,file_name);
    int res = rename(oldPath, newPath);
    return res;
}


int chooseNum() {
    printPrompt2();
    char *command = readCommand();
    if (strcmp(command, "exit\n") == 0) {
        free(command);
        return -1;
    }
    if (strcmp(command, "\n") == 0) {
        printf("File should be moved now.\n");
        free(command);
        return -2;
    }
    command[strlen(command)-1] = '\0'; // cut of \n at the end of command to convert it to int
    if (!isNumber(command)) {
        printf("Input should be a number.\n");
        return -3;
    }
    int num = atoi(command);
    free(command);
    printf("Directory should be changed now: %d\n", num);
    return num;
}


int isNumber(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}