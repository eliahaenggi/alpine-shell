#include "reader.h"
#include "shell.h"

#include <errno.h>

/**
 * Increments index and returns char at current position. Returns a end of file char if end is reached.
 */
char incrementIndex(reader* reader) {
    reader->index++;
    if (reader->index >= reader->cmdLength) {
        reader->index = reader->cmdLength;
        return EOF;
    }

    return reader->cmd[reader->index];
}

/**
 * Decrements Index field. If index is -1 it stays the same.
 */
void decrementIndex(reader* reader) {
    if (reader->index < 0) {
        return;
    }
    reader->index--;
}

/**
 * Returns char which should be read next. Index is not incremented.
 */
char getChar(reader* reader) {
    int pos = reader->index;
    pos++;

    if (pos >= reader->cmdLength) {
        return EOF;
    }

    return reader->cmd[pos];
}

/**
 * Increments index until char is no white space anymore.
 */
void skipWhiteSpaces(reader* reader) {
    char ch = getChar(reader);
    while (ch != EOF) {
        if (ch != ' ' && ch != '\t') { // Break if char is no white space or tab
            break;
        }
        ch = incrementIndex(reader);
    }
}
