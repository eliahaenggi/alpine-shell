#ifndef RENAME_H
#define RENAME_H
#include <dirent.h>

// the name of the old file
char old_filename [260];

// the location of the old file
DIR *dir;

int setOldFileName(char* name);

int renameFile(char* oldName, char* newName);

#endif
