#include "dll.h"

Node* DLL_NewNode(DataType newdata) {
    // allocate node and init.
    Node* ret = (Node*)malloc(sizeof(Node));
    if (ret == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);  // exit the program when memory allocation failed.
    }

    ret->data = newdata;
    ret->next = ret;
    ret->prev = ret;

    return ret;
}
bool DLL_exist(Node** head, Node* target) {
    if (*head == NULL) return false;
    for (Node* curr = (*head)->next; curr != *head; curr = curr->next) {
        if (curr == target) return true;
    }
    return *head == target;
}
void DLL_DelNode(Node** head, Node* target) {
    if (*head == NULL || target == NULL) {
        fprintf(stderr, "Invalid input: head(%p), target(%p)\n", (void*)*head, (void*)target);
        return; 
    }
    if (!DLL_exist(head, target)) {
        fprintf(stderr, "No such Node(%d) in List %d.\n", target->data, (*head)->data);
        return;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;
    if (target == *head) *head = target->next;
    if (DLL_Len(head) == 1) *head = NULL;
    
    free(target);
}
void DLL_Append(Node** head, Node* newnode) {
    if (newnode == NULL) {
        fprintf(stderr, "Invalid input: newnode(%p)\n", (void*)newnode);
        exit(EXIT_FAILURE);  
    }
    if (*head == NULL) {
        *head = newnode;
        newnode->next = newnode;
        newnode->prev = newnode;
        return;
    }
    
    Node* tail = (*head)->prev;
    DLL_Insert(tail, newnode);
}
void DLL_Insert(Node* target, Node* newnode) {
    if (target == NULL || newnode == NULL) {
        fprintf(stderr, "Invalid input: target(%p), newnode(%p)\n", (void*)target, (void*)newnode);
        exit(EXIT_FAILURE);
    }

    newnode->prev = target;
    newnode->next = target->next;

    target->next = newnode;
    newnode->next->prev = newnode;
}
DataType DLL_Pop(Node** head) {
    if (*head == NULL) {
        fprintf(stderr, "Empty List");
        exit(EXIT_FAILURE);  
    }
    Node* tail = (*head)->prev;
    DataType ret = tail->data;
    DLL_DelNode(head, tail);

    return ret;
}
Node* DLL_Get(Node** head, DataType search) {
    if (*head == NULL) {
        fprintf(stderr, "Invalid input: head(%p)\n", (void*)head);
        return NULL;
    }
    if ((*head)->data == search) return *head;
    for (Node* curr = (*head)->next; curr != *head; curr = curr->next) {
        if(curr->data == search) return curr;
    }
    return NULL;
}
int DLL_index(Node** head, Node* target) {
    if (*head == NULL || target == NULL) {
        fprintf(stderr, "Invalid input: head(%p), target(%p)\n", (void*)head, (void*)target);
        exit(EXIT_FAILURE);
    }
    if (*head == target) return 0;

    int ret = 1;
    for (Node* curr = (*head)->next; curr != *head; curr = curr->next, ret++) {
        if (curr == target) return ret;
    }
    return -1;
}
int DLL_Len(Node** head) {
    if (*head == NULL) return 0;
    int len = 0;
    Node* curr = *head;
    while (curr != NULL) {
        curr = curr -> next;
        len++;
        if (curr == *head) return len;
    }
    return 0;
}
void DLL_Replace(Node** head, DataType from, DataType to) {
    if (*head == NULL) return;

    Node* curr = *head;
    do {
       if (curr->data == from) curr->data = to;
       curr = curr->next; 
    } while (curr != *head);
}
void DLL_Print(Node** head) {
    Node* curr = *head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);    
        curr = curr->next;

        if (curr == *head) break;
    } 
    printf("END\n");
}
void DLL_PrintReverse(Node** head) {
    Node* curr = *head ? (*head)->prev : NULL;
    while (curr != NULL) {
        printf("%d -> ", curr->data);    
        curr = curr->prev;

        if (curr == (*head)->prev) break;
    }
    printf("END\n");
}
void DLL_Swap(Node** head, Node* a, Node* b) {
    int sum = a->data + b->data;
    a->data = sum - a->data;
    b->data = sum - b->data;
}