#include "eval.h"

int kindof(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') return OPERAND;
    if ('0' <= c && c <= '9') return NUMBER;
    if (c == '(' || c == ')') return PAREN;
    return 0;
}
char* gettoken(char* string) {
    int start = 0;
    int end = 0;
    for(int i = 0; string[i]; i++) {
        if (string[i] == ' ') continue;
        
        if (kindof(string[i]) == NUMBER) {
            start = i;
            break;
        }
        if (kindof(string[i]) == OPERAND || kindof(string[i]) == PAREN) {
            char* ret = (char*)malloc(2);
            ret[0] = string[i];
            ret[1] = '\0';
            return ret;
        }
    }
    // number case
    for(end = start; kindof(string[end]) == NUMBER; end++);
    int len = end - start;
    char* ret = (char*)malloc(len + 1);
    for(int i = 0; i < len; i++) {
        ret[i] = string[start + i];
    }
    ret[len] = '\0';
    return ret;
}
char* postfix(char* infix) {
    char* ret = (char*)malloc(2 * strlen(infix) + 1);
    ret[0] = '\0';
    char* token;
    Stack* tokenstack = LS_init();
    
    for (int i = 0; infix[i]; i += strlen(token)) {
        while (infix[i] == ' ') i++;

        token = gettoken(&infix[i]);
        if (kindof(token[0]) == NUMBER) {
            strcat(ret, token);
            strcat(ret, " ");
        }
        else if (LS_isEmpty(tokenstack) || LS_peek(tokenstack)[0] == '(' || token[0] == '(') {
            LS_push(tokenstack, token);
        }
        else if (token[0] == ')') {
            while (LS_peek(tokenstack)[0] != '(') {
                strcat(ret, LS_pop(tokenstack));
                strcat(ret, " ");
            }
            LS_pop(tokenstack);
        }
        else if ((token[0] == '*' || token[0] == '/') && (LS_peek(tokenstack)[0] == '+' ||LS_peek(tokenstack)[0] == '-')) {
            LS_push(tokenstack, token);
        }
        else { // token has high priority than top element.
            while (LS_peek(tokenstack) && LS_peek(tokenstack)[0] != '(') {
                strcat(ret, LS_pop(tokenstack));
                strcat(ret, " ");
            }
            LS_push(tokenstack, token);
        }
    }

    while (LS_peek(tokenstack)) {
        strcat(ret, LS_pop(tokenstack));
        strcat(ret, " ");
    }

    LS_del(&tokenstack);
    return (char*)realloc(ret, strlen(ret) + 1);
}
char* eval(char* input) {
    input = postfix(input);
    Stack* num = LS_init();
    char* token;

    for(int i = 0; input[i]; ) {
        if (input[i] == ' ') {i++; continue;}

        token = gettoken(&input[i]);
        i += strlen(token);

        if (kindof(token[0]) == NUMBER) {
            LS_push(num, token);
        }
        else if (kindof(token[0]) == OPERAND) {
            int b = atoi(LS_pop(num));
            int a = atoi(LS_pop(num));
            char res[1000];
            if (token[0] == '+') {
                sprintf(res, "%d", a + b);
                LS_push(num, res);
            }
            else if (token[0] == '-') {
                sprintf(res, "%d", a - b);
                LS_push(num, res);
            }
            else if (token[0] == '*') {
                sprintf(res, "%d", a * b);
                LS_push(num, res);
            }
            else if (token [0] == '/') {
                sprintf(res, "%d", a / b);
                LS_push(num, res);
            }
        }
    }
    char* ret = LS_pop(num);
    LS_del(&num);
    return ret;
}
int tokenToInt(char* token) {
    int t = atoi(token);
    return t >= 8 ? t + 4 : t;
}
BTNode* recursive_expression_tree(Stack* tokens) {
    if (tokens == NULL || LS_len(tokens) == 0) return NULL;

    BTNode* node;
    char* token = LS_pop(tokens);

    while (token[0] == '(' || token[0] == ')') token = LS_pop(tokens);

    if ('0' <= token[0] && token[0] <= '9') 
        return BT_createNode(tokenToInt(token));
    else if (token[0] == '+') node = BT_createNode(PLUS);
    else if (token[0] == '-') node = BT_createNode(MINUS);
    else if (token[0] == '*') node = BT_createNode(TIMES);
    else if (token[0] == '/') node = BT_createNode(DIVID);

    node->right = recursive_expression_tree(tokens);
    node->left = recursive_expression_tree(tokens);

    return node;
}
BTNode* expression_tree(char* input) {
    input = postfix(input);

    Stack* tokens = LS_init();
    char* token = NULL;

    for(int i = 0; input[i]; ) {
        while (input[i] == ' ') i++;

        token = gettoken(&input[i]);
        i += strlen(token);

        if (token[0]) LS_push(tokens, token);
    }
    
    return recursive_expression_tree(tokens);
}
int eval_tree_recursive(BTNode* root) {
    if (root == NULL) return 0;
    int data = root->data;
    int left = eval_tree_recursive(root->left);
    int right = eval_tree_recursive(root->right);

    switch (data) {
        case PLUS:  return left + right;
        case MINUS: return left - right;
        case TIMES: return left * right;
        case DIVID: return left / right;
        default:    return data >= 12 ? data - 4 : data;
    }
}
int eval_tree(char* input) {
    BTNode* root = expression_tree(input);
    int ret = eval_tree_recursive(root);
    BT_destroyTree(root);
    return ret;
}