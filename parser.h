#ifndef PARSER_H
#define PARSER_H
#include "tokenizer.h"

typedef enum cmdType {
    delete,
    move,
    re_name,
    show_files,
    show_dir,
    error // wrong argument -> TODO: Has to be handled
}cmdType;

typedef struct node {
    token tok;
    struct node* next;
}node;

typedef struct cmd {
    cmdType type;
    node* head;
}cmd;

cmd* createCommand();
void freeCommand(cmd* command);
void setCmdType(cmd* command);
void addNodeToList(node* n, cmd* command);
node* createNode(token* tok);
#endif
