#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 *  Creates a new cmd object on the heap with head == Null and type == error.
 */
cmd* createCommand() {
    cmd* cmdptr = malloc(sizeof(cmd));
    cmdptr->head = NULL;
    cmdptr->type = error;
    cmdptr->length = 0;
    return cmdptr;
}

/**
 * Frees command and every node in the command from the heap.
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
 * Creates a node on the heap with the specified token. Used to be placed in the linked list of cmd.
 */
node* createNode(struct token* tok) {
    node* n = malloc(sizeof(node));
    n->tok = *tok;
    n->next = NULL;
    return n;
}

/**
 * Adds a node to the end of the command linked list. If head is not set, node is new head. Every call length filed is
 * incremented.
 */
void addNodeToList(node* n, cmd* command) {
    command->length++;
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
    if (strcmp(headTok.text,"show") == 0) {
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
    if (strcmp(headTok.text,"copy") == 0) {
        command->type = copy;
        return;
    }
    if (strcmp(headTok.text,"go") == 0) {
        command->type = go;
        return;
    }
    if (strcmp(headTok.text,"run") == 0) {
        command->type = run;
        return;
    }
    if (strcmp(headTok.text,"help") == 0) {
        command->type = help;
        return;
    }
    command->type = error;
}


