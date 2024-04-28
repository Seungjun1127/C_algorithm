#include "liststack.h"
#include <string.h>

Stack* LS_init() {
    Stack* ret  = (Stack*)malloc(sizeof(Stack));
    ret->top    = NULL;
    ret->list   = NULL;
    ret->len    = 0;
    return ret;
}
void LS_del(Stack** ls) {
    if (*ls == NULL) return;
    while (LS_pop(*ls));
    free(*ls);
    *ls = NULL;
}
void LS_push(Stack* ls, char* data) {
    Node* newnode = (Node*)malloc(sizeof(Node));

    newnode->data = (char*)malloc(strlen(data) + 1);
    strcpy(newnode->data, data);

    newnode->next = ls->top;

    if (ls->list == NULL) ls->list = newnode;
    ls->top = newnode;
    ls->len++;
}
char* LS_pop(Stack* ls) {
    if (ls == NULL || LS_isEmpty(ls)) return NULL;
    if (LS_len(ls) == 1) ls->list = NULL;

    Node* topnode = ls->top;
    
    char* ret = (char*)malloc(strlen(topnode->data) + 1);
    strcpy(ret, topnode->data);

    ls->top = topnode->next;
    ls->len--;

    free(topnode);
    return ret;
}
char* LS_peek(Stack* ls) {
    if (ls == NULL || LS_isEmpty(ls) || ls->top == NULL ) return NULL;
    return ls->top->data;
}
bool LS_isEmpty(Stack* ls) {
    return ls ? ls->len == 0 : true;
}
int LS_len(Stack* ls) {
    return ls ? ls->len : 0;
}
void LS_print(Stack* ls) {
    if (ls == NULL || LS_isEmpty(ls)) return;

    Node* curr = ls->top;
    printf("[Top Element]\n");
    while (curr != ls->list) {
        printf("[%s]\n", curr->data);
        curr = curr->next;
    }
    printf("[%s]\n", ls->list->data);
    printf("[Bottom Element]\n\n");
}
void LS_test() {
    // 테스트를 위한 스택 초기화
    Stack* stack = LS_init();

    // 1. 빈 스택에서 Pop 또는 Peek 시도
    printf("Test 1: Pop or Peek from an empty stack:\n");
    printf("Pop: %s\n", LS_pop(stack));
    printf("Peek: %s\n\n", LS_peek(stack));

    // 2. 스택이 비어 있는 상태에서 Pop 또는 Peek 시도 후 Push
    printf("Test 2: Pop or Peek from an empty stack and then Push:\n");
    printf("Pop: %s\n", LS_pop(stack));
    printf("Peek: %s\n", LS_peek(stack));
    LS_push(stack, "Element 1");
    printf("After Push, Peek: %s\n\n", LS_peek(stack));

    // 3. 스택이 비어 있는 상태에서 여러 번 Pop 또는 Peek 시도
    printf("Test 3: Multiple Pop or Peek attempts from an empty stack:\n");
    for (int i = 0; i < 3; ++i) {
        printf("Pop %d: %s\n", i + 1, LS_pop(stack));
        printf("Peek %d: %s\n", i + 1, LS_peek(stack));
    }
    printf("\n");

    // 4. 스택에 여러 원소를 차례로 Push
    printf("Test 4: Push multiple elements to the stack:\n");
    LS_push(stack, "Element 2");
    LS_push(stack, "Element 3");
    LS_push(stack, "Element 4");
    printf("After Pushes, Peek: %s\n\n", LS_peek(stack));
    LS_print(stack);

    // 5. 스택이 가득 찬 상태에서 Push 시도
    printf("Test 5: Push to a full stack (with limited capacity):\n");
    for (int i = 0; i < 5; ++i) {
        char element[20];
        snprintf(element, sizeof(element), "+ ", i + 5);
        LS_push(stack, element);
    }
    printf("After pushing to a full stack, Peek: %s\n\n", LS_peek(stack));

    // 6. 스택의 길이 확인
    printf("Test 6: Check the length of the stack:\n");
    printf("Stack length: %d\n\n", LS_len(stack));
    LS_print(stack);
}