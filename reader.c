#include <errno.h>
#include "shell.h"
#include "reader.h"

/**
 * Returns char at current index and increments index field
 */
char incrementIndex(reader *reader) {
    reader->index++;
    if (reader->index >= reader->cmdLength) {
        reader->index = reader->cmdLength;
        return EOF;
    }

    return reader->cmd[reader->index];
}

/**
 * Decrements Index field by one
 */
void decrementIndex(reader *reader) {
    if (reader->index < 0) {
        return;
    }
    reader->index--;
}

/**
 * Returns char at current index
 */
char getChar(reader *reader) {
    if (!reader || !reader->cmd) {
        return ERRCHAR;
    }

    long pos = reader->index;
    pos++;

    if (pos >= reader->cmdLength) {
        return EOF;
    }

    return reader->cmd[pos];
}

/**
 * Increments index until char is no white space anymore
 */
void skipWhiteSpaces(reader *reader) {
    if (!reader || !reader->cmd) {
        return;
    }
    char c = getChar(reader);
    while (c != EOF) {
        if (c != ' ' && c != '\t') { // Break if char is no white space
            break;
        }
        c = incrementIndex(reader);
    }
}
