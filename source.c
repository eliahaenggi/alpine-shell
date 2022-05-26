#include <errno.h>
#include "shell.h"
#include "source.h"

char increaseIndex(struct source_s *src) {
    if(++src->index >= src->bufsize) {
        src->index = src->bufsize;
        return EOF;
    }

    return src->buffer[src->index];
}


void decreaseIndex(struct source_s *src) {
    if(src->index < 0) {
        return;
    }

    src->index--;
}


char getChar(struct source_s *src) {
    if(!src || !src->buffer) {
        return ERRCHAR;
    }

    long pos = src->index;
    pos++;

    if(pos >= src->bufsize) {
        return EOF;
    }

    return src->buffer[pos];
}


void skipWhiteSpaces(struct source_s *src) {
    char c;

    if(!src || !src->buffer) {
        return;
    }

    while(((c = getChar(src)) != EOF) && (c == ' ' || c == '\t')) {
        increaseIndex(src);
    }
}
