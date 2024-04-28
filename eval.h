#include "liststack.h"
#include "binarytree.h"

#define OPERAND 5
#define NUMBER 6
#define PAREN 7
#define PLUS 8
#define MINUS 9
#define TIMES 10
#define DIVID 11

int kindof(char c);
char* gettoken(char* string);
char* postfix(char* infix);
char* eval(char* postfix);
BTNode* recursive_expression_tree(Stack* tokens);
BTNode* expression_tree(char* input);
int eval_tree(char* input);