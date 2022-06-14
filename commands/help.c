#include "help.h"
#include <stdio.h>

int printHelp() {
    printf(" \033[1;33mshow\033[0m      -- list all directories and files\n");
    printf(" \033[1;33mshowdir\033[0m   -- list all directories\n");
    printf(" \033[1;33mshowfiles\033[0m -- list all files\n");
    printf(" \033[1;33mgo\033[0m        -- move directories\n");
    printf(" \033[1;33mrename\033[0m    -- rename a file\n");
    printf(" \033[1;33mdelete\033[0m    -- delete a file\n");
    printf(" \033[1;33mmove\033[0m      -- move a file\n");
    printf(" \033[1;33mcopy\033[0m      -- copy a file\n");
    printf(" \033[1;33mrun\033[0m       -- execute operating system command\n");
    return 0;
}
