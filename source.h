
#ifndef SHELL_PROJECT_SOURCE_H
#define SHELL_PROJECT_SOURCE_H

#define EOF             (-1)
#define ERRCHAR         ( 0)


struct source_s
{
    char *buffer;       /* the input text */
    long bufsize;       /* size of the input text */
    long index;       /* absolute char position in source */
};

char increaseIndex(struct source_s *src);
void decreaseIndex(struct source_s *src);
char getChar(struct source_s *src);
void skipWhiteSpaces(struct source_s *src);

#endif //SHELL_PROJECT_SOURCE_H
