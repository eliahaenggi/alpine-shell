#ifndef RENAME_H
#define RENAME_H
#include <dirent.h>

// the name of the old file
static char old_filename [260];

// the location of the old file
static DIR *dir;

int setOldFileName(char* name);

int renameFile(char* oldName, char* newName);

#endif
