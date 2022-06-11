//
// Created by Matthew on 10/06/2022.
//

#include <dirent.h>
#include <stdio.h>
#include "show_dir.h"

DIR current_dir;

//function which takes a string of a location, prints the name of all files and directories inside the location,
// and returns an arraylist, containing all filenames
struct names_node show(int argc, char **argv) {
    struct names_node* beginning= NULL;
    struct names_node* current;
    beginning->next = current;
    int i = 0;
    printf("started: \n \r");
    DIR *dir;
    dir = opendir("./");
    struct dirent *ep;
    if (dir != NULL) {
        while ((ep = readdir(dir))) {
            printf("(%d) %s",i, ep->d_name);
            printf("\r\n");
            strcpy(current->name,ep->d_name);
            current=current->next;
            i++;
        }
    }
    return ;
}