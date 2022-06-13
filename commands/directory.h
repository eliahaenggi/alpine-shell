//
// Created by Matthew on 10/06/2022.
//

#ifndef CLASSIC_C_SHOW_DIR_H
#define CLASSIC_C_SHOW_DIR_H

#endif //CLASSIC_C_SHOW_DIR_H
#include <dirent.h>
#include <limits.h>

static char cwd[PATH_MAX];
static char new_path[PATH_MAX];
static struct names_node *current_files;

//Function shows all files current directory and sets up names_node
struct names_node show_content();

//Deletes the current names list
void delete_names_list();

//Contains all the names in current directory
struct names_node{
    char name [260];
    int number;
    struct names_node* next;
};

void print_current_dir();

int show_directories();
int show_files_();

// Name and location of the current directory
//DIR current_directory;

// changes into the newly specified directory
void change_directory(int number);

// Exits the current directory and opens the containing one
DIR exit_directory();

int make_directory();
