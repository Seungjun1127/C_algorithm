#ifndef SLL_H
#define SLL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;

typedef struct _Node {
    DataType data;
    struct _Node* next;
} Node;

typedef struct list {
    Node* head;
    Node* tail;
    int len;
} List;

List* list_init();
Node* newnode(DataType data);

void delnode(List* list, int index);
void append(List* list, DataType data);
void insert(List* list, DataType data, int index);

Node* getnode(List* list, int index);
DataType get(List* list, int index);
int find(List* list, DataType data);
int len(List* list);

void finish_list(List* list);

#endif