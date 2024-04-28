#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;

typedef struct _arraystack {
    int capacity;
    int top;
    DataType* data;
} ArrayStack;

ArrayStack* AS_CreateArrayStack(int capa);
void AS_DeleteArrayStack(ArrayStack* as);
void AS_Resize(ArrayStack** as);
void AS_Push(ArrayStack** as, DataType data);
DataType AS_Pop(ArrayStack* as);
DataType AS_Peek(ArrayStack* as);
bool isEmpty(ArrayStack* as);
bool isFull(ArrayStack* as);
void AS_test();

#endif