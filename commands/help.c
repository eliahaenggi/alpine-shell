#include "help.h"

#include <stdio.h>

int printHelp() {
    printf(" \033[1;36mshow\033[0m                         -- list all directories and files\n");
    printf(" \033[1;36mshowdir\033[0m                      -- list all directories\n");
    printf(" \033[1;36mshowfiles\033[0m                    -- list all files\n");
    printf(" \033[1;36mgo\033[0m                           -- choose directory to go to\n");
    printf(" \033[1;36mrename <old_name> <new_name>\033[0m -- rename file\n");
    printf(" \033[1;36mdelete\033[0m                       -- choose file to delete\n");
    printf(" \033[1;36mdelete <file_name>\033[0m           -- delete file\n");
    printf(" \033[1;36mmove\033[0m                         -- choose path to move file\n");
    printf(" \033[1;36mmove <old_path> <new_path>\033[0m   -- move file\n");
    printf(" \033[1;36mcopy\033[0m                         -- copy file\n");
    printf(" \033[1;36mcopy <old_path> <new_path>\033[0m   -- choose path to copy file\n");
    printf(" \033[1;36mrun <command>\033[0m                -- execute operating system command\n");
    printf(" \033[1;36mhelp<command>\033[0m                -- get command informations\n");
    printf(" \033[1;36mexit<command>\033[0m                -- quit shell\n");
    return 0;
}
