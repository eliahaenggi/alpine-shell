//
// Created by Matthew on 10/06/2022.
//

//#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory.h"

struct names_node *current_files;
DIR *current_directory;

// function which takes a string of a location, prints the name of all files and directories inside the location,
// and saves a linked list, containing all filenames
struct names_node show_content() {
    delete_names_list();
    struct names_node *beginning = NULL;
    beginning = (struct names_node *) malloc(sizeof(struct names_node));

    struct names_node *temp = NULL;
    temp = (struct names_node *) malloc(sizeof(struct names_node));

    beginning->next = temp;

    printf("started: \n \r");
    DIR *dir;

    // TODO open correct directory and save in global variable
    if (!(dir = opendir("./."))) {
        printf("Error, could not find specified folder");
        //return ;
    }
    struct dirent *ep;

    if (dir != NULL) {
        int i = 0;
        ep = readdir(dir);
        while (1) {
            if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) {
                ep = readdir(dir);
            } else {
                printf("(%d) %s", i, ep->d_name);
                printf("\r\n");
                strcpy(temp->name, ep->d_name);
                temp->number = i;
                ep = readdir(dir);
                if (!ep) break;
                temp->next = (struct names_node *) malloc(sizeof(struct names_node));
                temp = temp->next;
                i++;
            }


        }
        temp = NULL;
    }
    // TODO delete till return (used for debugging)
    temp = beginning;
    while (temp->next != NULL) {
        temp = temp->next;
        printf("(%d) %s \r\n", temp->number, temp->name);
    }
    current_files = beginning;
    current_directory=dir;
    print_current_dir();
    return *beginning;
}

void delete_names_list() {
    if (current_files == NULL) return;
    struct names_node *tmp;

    while (current_files != NULL) {
        tmp = current_files;
        current_files = current_files->next;
        free(tmp);
    }
}

void print_current_dir() {
    DIR *dir;
    // TODO access directory from global variable
    dir = opendir("./");
    printf(dir->dd_name);
}

DIR change_directory(char directory_name[260]) {

}