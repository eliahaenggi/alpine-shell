#ifndef READER_H
#define READER_H

#define EOF (-1)

typedef struct reader
{
    char* cmd; // string containing the whole command
    int cmdLength; // size of the command
    int index; // position that signals which chars are already read

}reader;

char incrementIndex(reader* reader);
void decrementIndex(reader* reader);
char getChar(reader* reader);
void skipWhiteSpaces(reader* reader);

#endif
