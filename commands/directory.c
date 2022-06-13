//
// Created by Matthew on 10/06/2022.
//

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "directory.h"

char cwd[PATH_MAX];
struct names_node *filesAndDirectories;
struct names_node *files;
struct names_node *directories;

DIR *current_directory;
struct stat file_info;

// function which takes a string of a location, prints the name of all files and directories inside the location,
// and saves a linked list, containing all filenames(called directly by other commands, or with command "show")
struct names_node show_content() {
    delete_linked_list(filesAndDirectories);
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
        //TODO add error handling

        // return ;
    }
    //print_current_dir();
    rewinddir(dir);
    struct dirent *ep;

    if (dir != NULL) {
        int i = 0;
        ep = readdir(dir);
        while (1) {
            if (strcmp(ep->d_name, ".") == 0) {
                ep = readdir(dir);
            } else if (strcmp(ep->d_name, "..") == 0) {
                printf("(%d) \"go out 1 directory\"", i);
                if (S_ISDIR(file_info.st_mode)) {
                    printf(" (directory)");
                }
                printf("\r\n");
                strcpy(temp->name, ep->d_name);
                temp->number = i;
                ep = readdir(dir);
                if (!ep) break;
                temp->next = (struct names_node *) malloc(sizeof(struct names_node));
                temp = temp->next;
                i++;
            } else {
                stat(ep->d_name, &file_info);
                if (S_ISREG(file_info.st_mode)) {
                    printf("(%d) %s", i, ep->d_name);
                } else if (S_ISDIR(file_info.st_mode)) {
                    printf("\033[0;36m(%d) %s\033[0m", i, ep->d_name);
                }
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
        temp->next = NULL;
    }
    // TODO delete till return (used for debugging)

    filesAndDirectories = beginning;
    current_directory = dir;
    temp = beginning;

    while (temp->next != NULL) {
        temp = temp->next;
        //printf("(%d) %s \r\n", temp->number, temp->name);
    }

    getcwd(cwd, PATH_MAX);
    print_current_dir();
    return *beginning;
}

int show_files_() {
    delete_linked_list(files);

    struct names_node *beginning = NULL;
    beginning = (struct names_node *) malloc(sizeof(struct names_node));

    struct names_node *temp = NULL;

    temp = beginning;

    DIR *dir;
    getcwd(cwd, PATH_MAX);
    dir = opendir(cwd);

    rewinddir(dir);
    struct dirent *ep;
    if (dir == NULL) return -1;

    int i = 0;
    ep = readdir(dir);
    while (1) {
        if (!ep) break;
        stat(ep->d_name, &file_info);
        if (S_ISREG(file_info.st_mode)) {
            temp->next = (struct names_node *) malloc(sizeof(struct names_node));
            temp = temp->next;
            strcpy(temp->name, ep->d_name);
            temp->number = i;
            i++;
        }
        ep = readdir(dir);
    }
    //free(temp);
    temp->next = NULL;

    printf("files are:\r\n");
    files = beginning;
    temp = beginning;
    while (temp->next != NULL) {
        temp = temp->next;
        printf("(%d) %s \r\n", temp->number, temp->name);
    }
    return 0;
}

int show_directories() {
    delete_linked_list(directories);

    struct names_node *beginning = NULL;
    beginning = (struct names_node *) malloc(sizeof(struct names_node));

    struct names_node *temp = NULL;

    temp = beginning;

    DIR *dir;

    getcwd(cwd, PATH_MAX);
    dir = opendir(cwd);

    printf("current directory: %s", cwd);

    rewinddir(dir);
    struct dirent *ep;
    if (dir == NULL) return -1;

    int i = 0;
    ep = readdir(dir);
    while (1) {
        if (!ep) break;
        stat(ep->d_name, &file_info);
        if (S_ISDIR(file_info.st_mode) && strcmp(ep->d_name, ".") != 0) {
            temp->next = (struct names_node *) malloc(sizeof(struct names_node));
            temp = temp->next;
            strcpy(temp->name, ep->d_name);
            temp->number = i;
            i++;

        }
        ep = readdir(dir);
    }
    //free(temp);
    temp->next = NULL;

    printf("directories inside are:\r\n");
    directories = beginning;
    temp = beginning;
    while (temp->next != NULL) {
        temp = temp->next;
        if (strcmp(temp->name, "..") == 0) printf("(%d) \"go out by one directory\"\r\n", temp->number);
        else printf("(%d) %s \r\n", temp->number, temp->name);
    }
    return 0;
}

void delete_linked_list(struct names_node *pNode) {
    if (pNode == NULL) return;
    struct names_node *tmp;

    while (filesAndDirectories != NULL) {
        tmp = filesAndDirectories;
        filesAndDirectories = filesAndDirectories->next;
        free(tmp);
    }
}

void print_current_dir() {
    if (current_directory != NULL) {
        printf("current directory: \r\n %s \r\n", cwd);
        return;
    }

}

void change_directory(int number) {
    if (directories != NULL) {
        struct names_node *temp = directories;
        while (temp->next != NULL) {
            temp = temp->next;
            if (temp->number == number) {
                chdir(temp->name);
                //closedir(current_directory);
                //getcwd(cwd, sizeof cwd);
                //current_directory = opendir(cwd);
                //show_content();
                return;
            }
        }
    } else printf("WTF HAPPENED?");
}

