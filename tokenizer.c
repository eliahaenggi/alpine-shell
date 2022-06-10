#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
#include "tokenizer.h"
#include "reader.h"


char *tok_buf = NULL; // Store token
int tok_bufsize  = 0; // Store current allocated storage size
int tok_bufindex = -1; // Current buffer index

/* special token to indicate end of input */
token eof_token =
        {
                .length = 0,
        };

/**
 * Add Char to buffer. If bufindex equals bufsize, double bufsize.
 */
void addCharToBuffer(char c) {
    tok_buf[tok_bufindex] = c;
    tok_bufindex++;

    if (tok_bufindex >= tok_bufsize) {
        tok_bufsize = 2 * tok_bufindex;
        char *tmp = realloc(tok_buf, tok_bufsize);
        tok_buf = tmp;
    }
}

/**
 * Creates a new token struct with str as text and length.
 */
token *createToken(char *str) {
    token *tok = malloc(sizeof(token));

    memset(tok, 0, sizeof(token)); // fills tok with zeros
    tok->length = strlen(str);

    char *newstr = malloc((tok->length) + 1); // allocate new string on heap with length + 1

    strcpy(newstr, str);
    tok->text = newstr;
    return tok;
}

/**
 * Deallocates specified token and text in token.
 */
void freeToken(token *tok) {
    if (tok->text) {
        free(tok->text);
    }
    free(tok);
}

/**
 * Creates a new token with src struct. Calls createToken.
 */
struct token *tokenize(reader *reader) {
    //int endloop = 0;

    // Define tok_buf
    if (!tok_buf) {
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if (!tok_buf) {
            errno = ENOMEM;
            return &eof_token;
        }
    }

    tok_bufindex = 0;
    tok_buf[0] = '\0';

    char nc = incrementIndex(reader);

    if (nc == ERRCHAR || nc == EOF) {
        return &eof_token;
    }

    while (1) {
        if (nc == EOF) {
            break;
        }
        if (nc == ' '|| nc == '\t') {
            if (tok_bufindex > 0) {
                break;
            }
        }
        if (nc == '\n') {
            if (tok_bufindex > 0) {
                decrementIndex(reader);
            }// else {  Creates additional token with only slash n sign, not sure why.
            //    addCharToBuffer(nc);
            //}
            break;
        }
        addCharToBuffer(nc);
        nc = incrementIndex(reader);
    }
/*
    do {
        switch(nc) {
            case ' ':
            case '\t': // Check for tab character
                if (tok_bufindex > 0) {
                    endloop = 1;
                }
                break;

            case '\n': // Check for newline character
                if (tok_bufindex > 0) {
                    decreaseIndex(src);
                } else {
                    addCharToBuffer(nc);
                }
                endloop = 1;
                break;

            default:
                addCharToBuffer(nc);
                break;
        }

        if (endloop) {
            break;
        }

    } while ((nc = increaseIndex(src)) != EOF);
*/
    if (tok_bufindex == 0) {
        return &eof_token;
    }

    if (tok_bufindex >= tok_bufsize) {
        tok_bufindex--;
    }
    tok_buf[tok_bufindex] = '\0';
    token *tok = createToken(tok_buf);
    tok->reader = reader;
    return tok;
}