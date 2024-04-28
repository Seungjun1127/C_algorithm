#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;

typedef struct _Node {
    DataType data;
    struct _Node* prev;
    struct _Node* next;
} Node;

Node* DLL_NewNode(DataType newdata);
bool DLL_exist(Node** head, Node* target);
void DLL_DelNode(Node** head, Node* target);
void DLL_Append(Node** head, Node* newnode);
void DLL_Insert(Node* target, Node* newnode);
DataType DLL_Pop(Node** head);
Node* DLL_Get(Node** head, DataType search);
int DLL_index(Node** head, Node* target);
int DLL_Len(Node** head);
void DLL_Replace(Node** head, DataType from, DataType to);
void DLL_Print(Node** head);
void DLL_PrintReverse(Node** head);
void DLL_Swap(Node** head, Node* a, Node* b);

#endif