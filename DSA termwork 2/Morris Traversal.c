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

void morrisTraversal(struct TreeNode* root) {
    struct TreeNode* current = root;
    while (current != NULL) {
        if (current->left == NULL) {
            printf("%d ", current->val);
            current = current->right;
        } else {
            struct TreeNode* predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            if (predecessor->right == NULL) {
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = NULL;
                printf("%d ", current->val);
                current = current->right;
            }
        }
    }
}

void freeTree(struct TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
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

    // Perform Morris Traversal
    printf("\nMorris Traversal: ");
    morrisTraversal(root);
    printf("\n");

    // Free the memory allocated for the tree
    freeTree(root);

    return 0;
}

