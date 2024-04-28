#include "binarytree.h"

int max(int a, int b) {
    return a > b ? a : b;
}
BTNode* BT_createNode(int data) {
    BTNode* ret = (BTNode*)malloc(sizeof(BTNode));

    ret->left = NULL;
    ret->right = NULL;
    ret->data = data;

    return ret;
}
void BT_destroyNode(BTNode* node) {
    free(node);
}
void BT_destroyTree(BTNode* tree) {
    if (tree == NULL) return;

    BT_destroyTree(tree->right);
    BT_destroyTree(tree->left);
    BT_destroyNode(tree);
}
BTNode* BT_insert(BTNode* root, int data) {
    if (root == NULL) return BT_createNode(data);

    if (root->data > data) {
        if (root->left) return BT_insert(root->left, data);
        return root->left = BT_createNode(data); 
    }
    else {
        if (root->right) return BT_insert(root->right, data);
        return root->right = BT_createNode(data);
    }
}
void BT_delete(BTNode* root, int data);
void BT_search(BTNode* root, int data);
// order = 0 : inorder | 1 : preorder | -1 : postorder
void BT_traversal(BTNode* root, int order) {
    if (root == NULL) return;

    if (order == 0) {
        BT_traversal(root->left, order);
        printf("[%d] ", root->data);
        BT_traversal(root->right, order);
    }
    else if (order == 1) {
        printf("[%d] ", root->data);
        BT_traversal(root->left, order);
        BT_traversal(root->right, order);
    }
    else if (order == -1) {
        BT_traversal(root->right, order);
        printf("[%d] ", root->data);
        BT_traversal(root->left, order);
    }
    else printf("wrong order\n");
}   
int BT_min(BTNode* root) {
    return root->left ? BT_min(root->left) : root->data;
}
int BT_max(BTNode* root) {
    return root->right ? BT_max(root->right) : root->data;
}
int BT_height(BTNode* root) {
    return root ? 1 + max(BT_height(root->left), BT_height(root->right)): 0;
}
void BT_print_recursive(BTNode* root, int depth) {
    if (root == NULL) return;

    for(int i = 0; i < depth; i++)
        printf("  ");
    
    printf("| %d\n", root->data);

    BT_print_recursive(root->right, depth + 1);
    BT_print_recursive(root->left, depth + 1);
}
void BT_print(BTNode* root) {
    BT_print_recursive(root, 0);
}