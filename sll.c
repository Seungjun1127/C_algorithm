#include "sll.h"

List* list_init() {
    /* make new list. */
    List* ret = (List*)malloc(sizeof(List));

    ret->head = NULL;
    ret->tail = NULL;
    ret->len = 0;

    return ret;
}
Node* newnode(DataType data) {
    /* make new node. */    
    Node* ret = (Node*)malloc(sizeof(Node));
    ret->data = data;
    ret->next = NULL;

    return ret;
}
void delnode(List* list, int index) {
    while (index < 0) index = list->len + index;
    if (list == NULL || len(list) == 0 || len(list) <= index ) return;
    if (len(list) == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->len = 0;
        return;
    }
    if (index == 0) {
        Node* target = list->head;

        list->head = list->head->next;
        free(target);
        list->len--;
        return;
    }
    Node* prev = getnode(list, index-1);
    prev->next = prev->next->next;
    free(prev->next);
}
void append(List* list, DataType data) {
    Node* memb = newnode(data);
    if (list->tail == NULL) {
        list->head = memb;
        list->tail = memb;
    }
    else {
        list->tail->next = memb;
        list->tail = memb;
    }
    list->len++;
}
void insert(List* list, DataType data, int index) {
    /* push element to be i-th element. */
    while (index < 0) index = list->len + index;
    if (index > len(list)) return append(list, data);
    
    Node* memb = newnode(data);
    if (len(list) == 0) {
        list->head = memb;
        list->tail = memb;
        list->len = 1;
        return;
    }
    if (index == 0) {
        memb->next = list->head;
        list->head = memb;
        list->len++;
        return;
    }
    Node* prev = getnode(list, index-1);

    memb->next = prev->next;
    prev->next = memb;
    if (prev == list->tail) list->tail = memb;
}
Node* getnode(List* list, int index) {
    while (index < 0) index = list->len + index;
    if (index >= len(list)) return NULL;
    
    int i = 0;
    for (Node* curr = list->head; curr ; curr = curr->next, i++)
        if (i == index) return curr;
    return NULL;
}
DataType get(List* list, int index) {
    while (index < 0) index = list->len + index;
    return getnode(list, index)->data;
}
int find(List* list, DataType data) {
    int i = 0;
    for(Node* curr = list->head; curr; curr = curr->next, i++)
        if (curr->data == data) return i;
    return -1;
}
int len(List* list) {
    return list->len;
}
void finish_list(List* list) {
    for (Node* curr = list->head; curr ; curr = list->head) {
        list->head = list->head->next;
        free(curr);
    }
    free(list);
}