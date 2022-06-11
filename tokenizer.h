#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "reader.h"

typedef struct token {
    reader *reader; // source of input
    int length; // length of token text
    char *text; // token text
}token;

/* the special EOF token, which indicates the end of input */
extern token eof_token;

token *tokenize(reader *src);
void freeToken(token *tok);

#endif