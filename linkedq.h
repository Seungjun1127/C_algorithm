#ifndef LINKEDQ_H
#define LINKEDQ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sll.h"
#define EMPTY -999

typedef struct linkque {
    List* data;
} Linkque;

Linkque* init_queue();
void enqueue(Linkque* que, DataType data);
DataType dequeue(Linkque* que);
void print_queue(Linkque* que);
void finish_queue(Linkque* que);
void lq_test();

#endif