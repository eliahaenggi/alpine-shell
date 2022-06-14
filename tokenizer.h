#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "reader.h"

typedef struct token {
    reader* reader; // source of input
    int length; // length of token text
    char* text; // token text
}token;

// Token to mark end of the input
extern token eof_token;

token* tokenize(reader* src);
void freeToken(token* tok);

#endif