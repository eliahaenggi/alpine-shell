//
// Created by Matthew on 10/06/2022.
//

#ifndef CLASSIC_C_SHOW_DIR_H
#define CLASSIC_C_SHOW_DIR_H

#endif //CLASSIC_C_SHOW_DIR_H
struct names_node show(int argc, char **argv);
struct names_node{
    char name [260];
    struct names_node* next;
};