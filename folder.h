#ifndef FOLDER_H
#define FOLDER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _treenode_ {
    struct _treenode_* child;
    struct _treenode_* sibling;
    struct _treenode_* parent;
    char* name;
    char* data;
} TreeNode;

bool folder_compare(const char* s1, const char* s2);
TreeNode* folder_init();
TreeNode* folder_newnode(char* name, char* data, TreeNode* parent, TreeNode* sibling, TreeNode* child);
TreeNode* folder_newchild(TreeNode* parent, char* name);
TreeNode* folder_newsibling(TreeNode* first, char* name);
void folder_deletenode(TreeNode* root, TreeNode* destroy);
void folder_deletetree(TreeNode* root);
void folder_writedata(TreeNode* leaf, char* data);
char* folder_getdata(TreeNode* leaf);
TreeNode* folder_findfolder(TreeNode* root, char* name);
void folder_print(TreeNode* root);

#endif