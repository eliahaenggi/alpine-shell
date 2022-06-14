#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
#include "tokenizer.h"
#include "reader.h"


char* tokenText = NULL; // Store token
int tokenSize  = 0; // Store current allocated storage size
int tokenTextSize = -1; // Current text size

/**
 * Token with length == 0 to indicate end of input.
 */
token eof_token = { .length = 0 };

/**
 * Add Char to tokenText. If text size equals allocated storage, double storage size.
 */
void addCharToToken(char c) {
    tokenText[tokenTextSize] = c;
    tokenTextSize++;

    if (tokenTextSize >= tokenSize) {
        tokenSize = 2 * tokenTextSize;
        char *tmp = realloc(tokenText, tokenSize);
        tokenText = tmp;
    }
}

/**
 * Creates a new token struct with specified string as tokenText.
 */
token* createToken(char* str) {
    token *tok = malloc(sizeof(token));

    memset(tok, 0, sizeof(token)); // fills tok with zeros
    tok->length = strlen(str);

    char *newstr = malloc((tok->length) + 1); // allocate new string on heap with length + 1

    strcpy(newstr, str);
    tok->text = newstr;
    return tok;
}

/**
 * Creates a new token with specified reader. Calls createToken().
 */
struct token* tokenize(reader *reader) {
    // Define tokenText
    if (!tokenText) {
        tokenSize = 512;
        tokenText = malloc(512 * sizeof(char));
    }
    tokenTextSize = 0;
    tokenText[0] = '\0';

    char ch = incrementIndex(reader);
    if (ch == EOF) {
        return &eof_token;
    }
    while (1) {
        if (ch == EOF) {
            break;
        }
        if (ch == ' ' || ch == '\t') {
            if (tokenTextSize > 0) {
                break;
            }
        }
        if (ch == '\n') {
            if (tokenTextSize > 0) {
                decrementIndex(reader);
            }
            break;
        }
        addCharToToken(ch);
        ch = incrementIndex(reader);
    }
    if (tokenTextSize == 0) {
        return &eof_token;
    }
    if (tokenTextSize >= tokenSize) {
        tokenTextSize--;
    }
    tokenText[tokenTextSize] = '\0';
    token *tok = createToken(tokenText);
    tok->reader = reader;
    return tok;
}