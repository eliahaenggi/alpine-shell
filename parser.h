#ifndef PARSER_H
#define PARSER_H
#include "tokenizer.h"

typedef enum cmdType {
    delete,
    move,
    copy,
    re_name,
    directory,
    show_files,
    show_dir,
    go,
    run,
    error // wrong argument
}cmdType;

typedef struct node {
    token tok;
    struct node* next;
}node;

typedef struct cmd {
    cmdType type;
    node* head;
    int length;
}cmd;

cmd* createCommand();
void freeCommand(cmd* command);
void setCmdType(cmd* command);
void addNodeToList(node* n, cmd* command);
node* createNode(token* tok);
#endif
