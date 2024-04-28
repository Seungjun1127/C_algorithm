#include "folder.h"

bool folder_same(char* s1, char* s2) {
    int index = 0;
    while (s1[index] && s2[index]) {
        if (s1[index] != s2[index++]) return false;
    }
    return s1[index] == s2[index];
}
TreeNode* folder_init() {
    return folder_newnode("ROOT", NULL, NULL, NULL, NULL);
}
TreeNode* folder_newnode(char* name, char* data, TreeNode* parent, TreeNode* sibling, TreeNode* child) {
    TreeNode* ret = (TreeNode*)malloc(sizeof(TreeNode));

    ret->name = (char*)malloc(strlen(name) + 1);
    strcpy(ret->name, name);

    if (data) {
        ret->data = (char*)malloc(strlen(data) + 1);
        strcpy(ret->data, data);
    }
    else ret->data = NULL;
    
    ret->child = child;
    ret->sibling = sibling;
    ret->parent = parent;

    return ret;
}
TreeNode* folder_newchild(TreeNode* parent, char* name) {
    if (parent->child) return folder_newsibling(parent->child, name);
    return parent->child = folder_newnode(name,NULL,parent,NULL,NULL);
}
TreeNode* folder_newsibling(TreeNode* first, char* name) {
    TreeNode* last = first;
    while (last->sibling) last = last->sibling;

    return last->sibling = folder_newnode(name, NULL, first->parent, NULL, NULL);
}
void folder_deletenode(TreeNode* root, TreeNode* destroy) {
    if (root == NULL) return;
    if (destroy == NULL) return;

    if (root == destroy) {
       folder_deletetree(root);
       return; 
    }

    // if destroy node is not root, destroy have parent. and that parent->child is first elder one.
    TreeNode* first = destroy->parent->child;

    if (destroy == first) {
        // destroy node is first child. child change : first -> second.
        destroy->parent->child = first->sibling;
    }
    else if (destroy->sibling) {
        TreeNode* before = first;
        while ( before->sibling != destroy) before = before->sibling;

        // destroy node have sibling. connect to before node with next sibling.
        before->sibling = destroy->sibling;
    }

    if (destroy->child) folder_deletetree(destroy);
    else {
        // free single node.
        free(destroy->data);
        free(destroy->name);
        free(destroy);
    }
}
void folder_deletetree(TreeNode* root) {
    if (root == NULL) return;

    folder_deletetree(root->child);
    folder_deletetree(root->sibling);

    free(root->data);
    free(root->name);
    free(root);
}
void folder_writedata(TreeNode* leaf, char* data) {
    if (leaf == NULL) return;

    leaf->data = (char*)malloc(strlen(data) + 1);
    strcpy(leaf->data, data);
}
char* folder_getdata(TreeNode* leaf) {
    return leaf->data;
}
TreeNode* folder_findfolder(TreeNode* root, char* name) {
    if (root == NULL) return NULL;
    if (folder_same(root->name, name)) return root;

    TreeNode* ret = folder_findfolder(root->sibling, name);
    return ret ? ret : folder_findfolder(root->child, name);
}
void folder_print_recursive(TreeNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    // 같은 깊이의 노드는 같은 줄에 출력
    for (int i = 0; i < depth; ++i) {
        printf("  ");  // 2개의 공백을 출력하여 들여쓰기 수준 조절
    }

    printf("| %s\n", node->name);
    folder_print_recursive(node->child, depth + 1);
    folder_print_recursive(node->sibling, depth);
}
void folder_print(TreeNode* root) {
    folder_print_recursive(root, 0);
}