//
// Created by Matthew on 10/06/2022.
//

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "directory.h"

char cwd[PATH_MAX];

struct names_node *current_files;
DIR *current_directory;

// function which takes a string of a location, prints the name of all files and directories inside the location,
// and saves a linked list, containing all filenames(called directly by other commands, or with command "show")
struct names_node show_content() {
    delete_names_list();
    struct names_node *beginning = NULL;
    beginning = (struct names_node *) malloc(sizeof(struct names_node));

    struct names_node *temp = NULL;
    temp = (struct names_node *) malloc(sizeof(struct names_node));

    beginning->next = temp;

    DIR *dir;

    // TODO open correct directory and save in global variable
    if (current_directory != NULL) {
        dir = current_directory;
    } else if (!(dir = opendir("./."))) {
        printf("Error, could not find specified folder");
        //return ;
    }
    struct dirent *ep;

    if (dir != NULL) {
        int i = 0;
        ep = readdir(dir);
        while (1) {
            if (strcmp(ep->d_name, ".") == 0) {
                ep = readdir(dir);
            } else if (strcmp(ep->d_name, "..") == 0) {
                printf("(%d) \"go out 1 directory\"", i);
                printf("\r\n");
                strcpy(temp->name, ep->d_name);
                temp->number = i;
                ep = readdir(dir);
                if (!ep) break;
                temp->next = (struct names_node *) malloc(sizeof(struct names_node));
                temp = temp->next;
                i++;
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
    /**
    while (temp->next != NULL) {
        temp = temp->next;
        printf("(%d) %s \r\n", temp->number, temp->name);
    }


    **/
    current_files = beginning;
    current_directory = dir;
    //print_current_dir();
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
    if (current_directory != NULL) {
        printf("current directory: \r\n %s \r\n",current_directory->dd_name);
        return;
    }

}

void change_directory(int number) {
    if (current_directory!=NULL && current_files != NULL){
        struct names_node *temp = current_files;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->number==number){
                chdir(temp->name);
                closedir(current_directory);
                current_directory = opendir(getcwd(cwd, sizeof cwd));
                show_content();
                return;
            }
        }
    } else printf("WTF HAPPENED?");
}