#include "linkedq.h"

Linkque* init_queue() {
    Linkque* ret = (Linkque*)malloc(sizeof(Linkque));
    ret->data = list_init();
}
void enqueue(Linkque* que, DataType data) {
    insert(que->data, data, 0);
}
DataType dequeue(Linkque* que) {
    if (que->data->len == 0) return EMPTY;
    int ret = get(que->data, -1);
    delnode(que->data, -1);

    return ret;
}
void print_queue(Linkque* que) {
    if (len(que->data) <= 0) {
        printf("EMPTY QUEUE\n");
        return;
    }
    for(int i = 0; i < len(que->data); i++) {
        printf("[%d] ", get(que->data, i));
    }
    printf("\n\n");
}
void finish_queue(Linkque* que) {
    finish_list(que->data);
    free(que);
}
void lq_test() {
    printf("lq_test running");
    int capacity = 5;
    Linkque* queue = init_queue(capacity);

    // Enqueue elements
    for (int i = 1; i <= 3; ++i) {
        enqueue(queue, i);
        printf("Enqueued: %d\n", i);
    }

    print_queue(queue);
    printf("\n");

    // Dequeue elements
    for (int i = 0; i < 2; ++i) {
        int value = dequeue(queue);
        if (value != EMPTY) {
            printf("Dequeued: %d\n", value);
        } else {
            printf("Queue is empty\n");
        }
    }

    print_queue(queue);
    printf("\n");

    // Enqueue more elements
    for (int i = 4; i <= 7; ++i) {
        enqueue(queue, i);
        printf("Enqueued: %d\n", i);
    }

    print_queue(queue);
    printf("\n");

    // Dequeue all remaining elements
    while (queue->data->len) {
        int value = dequeue(queue);
        if (value != EMPTY) {
            printf("Dequeued: %d\n", value);
        } else {
            printf("Queue is empty\n");
        }
    }

    print_queue(queue);
    printf("\n");

    // Enqueue more elements
    for (int i = 4; i <= 10; ++i) {
        enqueue(queue, i);
        printf("Enqueued: %d\n", i);
    }

    print_queue(queue);
    printf("\n");

    finish_queue(queue);
    printf("\n");
}