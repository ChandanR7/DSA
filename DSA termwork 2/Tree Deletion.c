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

void postOrderDelete(struct TreeNode* node) {
    if (node == NULL)
        return;

    postOrderDelete(node->left);
    postOrderDelete(node->right);
    free(node);
}

void freeTree(struct TreeNode* root) {
    postOrderDelete(root);
}

int main() {
    // Create the binary tree
    struct TreeNode* root = NULL;
    int val, choice;
    printf("Enter the nodes of the binary tree (enter -1 to stop):\n");
    do {
        printf("Enter node value: ");
        scanf("%d", &val);
        if (val == -1)
            break;
        struct TreeNode* newNode = createNode(val);
        if (root == NULL)
            root = newNode;
        else {
            struct TreeNode* temp = root;
            while (1) {
                printf("Enter 1 to insert as left child, 2 to insert as right child of %d: ", temp->val);
                scanf("%d", &choice);
                if (choice == 1) {
                    if (temp->left == NULL) {
                        temp->left = newNode;
                        break;
                    } else {
                        temp = temp->left;
                    }
                } else if (choice == 2) {
                    if (temp->right == NULL) {
                        temp->right = newNode;
                        break;
                    } else {
                        temp = temp->right;
                    }
                }
            }
        }
    } while (1);

    // Perform post-order deletion
    freeTree(root);
    printf("Binary tree deleted successfully.\n");

    return 0;
}

