#include "arraystack.h"

// mack stack with given size.
ArrayStack* AS_CreateArrayStack(int capa) {
    ArrayStack* ret = (ArrayStack*)malloc(sizeof(ArrayStack));
    ret->capacity = capa;
    ret->top = 0;
    ret->data = (DataType*)malloc(sizeof(DataType) * capa);

    return ret;
}
// free stack.
void AS_DeleteArrayStack(ArrayStack* as) {
    free(as->data);
    free(as);
}
// resize the stack with 2 times of size.
void AS_Resize(ArrayStack** as) {
    ArrayStack* newstack = AS_CreateArrayStack((*as)->capacity * 2);

    for(int i = 0; i < (*as)->top; i++) {
        newstack->data[i] = (*as)->data[i];
    }
    newstack->top = (*as)->top;
    AS_DeleteArrayStack(*as);
    *as = newstack;
}
// push inputed data to stack.
void AS_Push(ArrayStack** as, DataType newdata) {
    if (isFull(*as)) AS_Resize(as);

    (*as)->data[((*as)->top)++] = newdata;
}
// return top element in stack. then delete the element. wrong assign, return 0.
DataType AS_Pop(ArrayStack* as) {
    if (isEmpty(as)) return 0;
    return as->data[--(as->top)];
}
// return top element in stack. wrong assign, return 0.
DataType AS_Peek(ArrayStack* as) {
    if (isEmpty(as)) return 0;
    return as->data[as->top - 1];
}
// return true when the stack is empty.
bool isEmpty(ArrayStack* as) {
    return as->top == 0;
}
// return true when the stack is Full.
bool isFull(ArrayStack* as) {
    return as->top == as->capacity;
}
// test arraystack data structure.
void AS_test() {
    // 테스트를 위한 스택 생성
    ArrayStack* stack = AS_CreateArrayStack(5);

    // 스택이 비어 있는지 확인
    printf("Is stack empty? %s\n", isEmpty(stack) ? "Yes" : "No");

    // 여러 원소를 스택에 푸시
    AS_Push(&stack, 10);
    AS_Push(&stack, 20);
    AS_Push(&stack, 30);
    AS_Push(&stack, 40);
    AS_Push(&stack, 50);

    // 스택이 가득 찼는지 확인
    printf("Is stack full? %s\n", isFull(stack) ? "Yes" : "No");

    // 스택의 top 원소 확인
    printf("Top element in stack: %d\n", AS_Peek(stack));

    // 스택의 원소 팝
    printf("Popped element: %d\n", AS_Pop(stack));

    // 스택이 비어 있는지 확인
    printf("Is stack empty? %s\n", isEmpty(stack) ? "Yes" : "No");

    // 여러 원소를 추가하여 resize 확인
    AS_Push(&stack, 60);
    AS_Push(&stack, 70);
    AS_Push(&stack, 80);

    // 스택의 top 원소 확인
    printf("Top element in stack: %d\n", AS_Peek(stack));

    // 스택 전체 비우기
    while (!isEmpty(stack)) {
        printf("Popped element: %d\n", AS_Pop(stack));
    }

    // 스택이 비어 있는지 확인
    printf("Is stack empty? %s\n", isEmpty(stack) ? "Yes" : "No");

    // 스택 삭제
    AS_DeleteArrayStack(stack);
}