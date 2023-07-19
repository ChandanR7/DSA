#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preOrderPrint(struct TreeNode* root) {
    if (root == NULL)
        return;

    printf("%d ", root->val);  // Print the current node

    preOrderPrint(root->left);  // Recursively print the left subtree

    preOrderPrint(root->right);  // Recursively print the right subtree
}

struct TreeNode* constructTree() {
    int val;
    printf("Enter the value (enter -1 for NULL): ");
    scanf("%d", &val);

    if (val == -1)
        return NULL;

    struct TreeNode* newNode = createNode(val);

    printf("Enter left child of %d:\n", val);
    newNode->left = constructTree();

    printf("Enter right child of %d:\n", val);
    newNode->right = constructTree();

    return newNode;
}

int main() {
    // Construct the binary tree
    printf("Constructing the binary tree:\n");
    struct TreeNode* root = constructTree();

    // Print the elements in prefix notation
    printf("\nPrefix notation:\n");
    preOrderPrint(root);

    return 0;
}

