#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 *  Creates a new cmd object on the heap with head and type == NULL.
 */
cmd* createCommand() {
    cmd* cmdptr = malloc(sizeof(cmd));
    cmdptr->head = NULL;
    cmdptr->type = (cmdType) NULL;
    cmdptr->length = 0;
    return cmdptr;
}

/**
 * Frees the cmd and every node in the command from the heap.
 */
void freeCommand(cmd* command) {
    node* currentNode = command->head;
    while(currentNode->next) {
        node* lastNode = currentNode;
        currentNode = currentNode->next;
        free(lastNode);
    }
    free(currentNode);
    free(command);
}

/**
 * Creates a node on the heap with the specified token.
 */
node* createNode(struct token* tok) {
    node* n = malloc(sizeof(node));
    n->tok = *tok;
    n->next = NULL;
    return n;
}

/**
 * Adds a node to the linked list of the command.
 */
void addNodeToList(node* n, cmd* command) {
    if (!command->head) {
        command->head = n;
        return;
    }
    node* currentNode = command->head;
    while(currentNode->next) {
        currentNode = currentNode->next;
    }
    currentNode->next = n;
}

/**
 * Sets the command type of the command with the head token. If command is unknown error enum is taken.
 */
void setCmdType(cmd* command) {
    token headTok = command->head->tok;
    if (strcmp(headTok.text,"delete") == 0) {
        command->type = delete;
        return;
    }
    if (strcmp(headTok.text,"move") == 0) {
        command->type = move;
        return;
    }
    if (strcmp(headTok.text,"rename") == 0) {
        command->type = re_name;
        return;
    }
    if (strcmp(headTok.text,"directory") == 0) {
        command->type = directory;
        return;
    }
    if (strcmp(headTok.text,"showdir") == 0) {
        command->type = show_dir;
        return;
    }
    if (strcmp(headTok.text,"showfiles") == 0) {
        command->type = show_files;
        return;
    }
    command->type = error;
}


