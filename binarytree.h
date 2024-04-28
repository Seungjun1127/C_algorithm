#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct binarytreenode {
    struct binarytreenode* left;
    struct binarytreenode* right;
    int data;
} BTNode;

BTNode* BT_createNode(int data);
void BT_destroyNode(BTNode* node);
void BT_destroyTree(BTNode* tree);
BTNode* BT_insert(BTNode* root, int data);
void BT_delete(BTNode* root, int data);
void BT_search(BTNode* root, int data);
void BT_traversal(BTNode* root, int order);
int BT_min(BTNode* root);
int BT_max(BTNode* root);
int BT_height(BTNode* root);
void BT_print(BTNode* root);

#endif