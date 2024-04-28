#ifndef LISTSTACK_H
#define LISTSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _node {
    char* data;
    struct _node* next;
} Node;

typedef struct _stack {
    Node* top;
    Node* list;
    int len;
} Stack;

Stack* LS_init();
void LS_del(Stack** ls);
void LS_push(Stack* ls, char* data);
char* LS_pop(Stack* ls);
char* LS_peek(Stack* ls);
bool LS_isEmpty(Stack* ls);
int LS_len(Stack* ls);
void LS_print(Stack* ls);
void LS_test();

#endif