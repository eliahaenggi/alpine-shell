#include <errno.h>
#include "shell.h"
#include "reader.h"

/**
 * Increments index and returns char at current position.
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
 * Returns char at current index. Index is not incremented.
 */
char getChar(reader* reader) {
    long pos = reader->index;
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
    if (!reader || !reader->cmd) {
        return;
    }
    char c = getChar(reader);
    while (c != EOF) {
        if (c != ' ' && c != '\t') { // Break if char is no white space or tab
            break;
        }
        c = incrementIndex(reader);
    }
}
