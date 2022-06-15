#include "tokenizer.h"
#include "shell.h"
#include "reader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char* tokenText = NULL; // Store current token
int tokenSize  = 0; // Store current allocated storage size
int tokenTextLength = -1; // Current text length

/**
 * Token to indicate end of input. Similar to EOF in reader.
 */
token EOFToken = { .length = 0 };

/**
 * Add Char to tokenText. If text size equals allocated storage, double storage size.
 */
void addCharToToken(char c) {
    tokenText[tokenTextLength] = c;
    tokenTextLength++;

    if (tokenTextLength >= tokenSize) {
        tokenSize = 2 * tokenTextLength;
        char *tmp = realloc(tokenText, tokenSize);
        tokenText = tmp;
    }
}

/**
 * Creates a new token struct with specified string as tokenText.
 */
token* createToken(char* text) {
    token *tok = malloc(sizeof(token));

    tok->length = strlen(text);

    char* string = malloc(tok->length); // allocate new string on heap

    strcpy(string, text);
    tok->text = string;
    return tok;
}

/**
 * Creates a new token with specified reader. Calls createToken().
 */
token* tokenize(reader *reader) {
    // Define tokenText
    if (!tokenText) {
        tokenSize = 512;
        tokenText = malloc(512 * sizeof(char));
    }
    tokenTextLength = 0;
    tokenText[0] = '\0';

    char ch = incrementIndex(reader);
    if (ch == EOF) {
        return &EOFToken;
    }
    while (1) {
        if (ch == EOF) {
            break;
        }
        if (ch == ' ' || ch == '\t') {
            if (tokenTextLength > 0) {
                break;
            }
        }
        if (ch == '\n') {
            if (tokenTextLength > 0) {
                decrementIndex(reader);
            }
            break;
        }
        addCharToToken(ch);
        ch = incrementIndex(reader);
    }
    if (tokenTextLength == 0) {
        return &EOFToken;
    }
    tokenText[tokenTextLength] = '\0';
    token *tok = createToken(tokenText);
    tok->reader = reader;
    return tok;
}