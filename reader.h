#ifndef READER_H
#define READER_H

#define EOF             (-1)
#define ERRCHAR         ( 0)


typedef struct reader
{
    char *cmd; // whole command
    long cmdLength; // size of the command
    long index; // index position in command
}reader;

char incrementIndex(reader *reader);
void decrementIndex(reader *reader);
char getChar(reader *reader);
void skipWhiteSpaces(reader *reader);

#endif //SHELL_PROJECT_READER_H
