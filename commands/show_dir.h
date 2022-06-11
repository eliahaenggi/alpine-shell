//
// Created by Matthew on 10/06/2022.
//

#ifndef CLASSIC_C_SHOW_DIR_H
#define CLASSIC_C_SHOW_DIR_H

#endif //CLASSIC_C_SHOW_DIR_H

//Function shows all files current directory and sets up names_node
struct names_node show(int argc, char **argv);

//Contains all the names in current directory
struct names_node{
    char name [260];
    int number;
    struct names_node* next;
};

// Name and location of the current directory
char current_location [260];

// changes into the newly specified directory
DIR change_directory(char directory_name [260]);

// Exits the current directory and opens the containing one
DIR exit_directory();
