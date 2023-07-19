#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

struct Stack {
    int top;
    char items[MAX_SIZE];
};

void push(struct Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->items[++(stack->top)] = item;
}

char pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->items[(stack->top)--];
}

int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

void infixToPostfix(char* infixExpression, char* postfixExpression) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    int i, j = 0;

    for (i = 0; i < strlen(infixExpression); i++) {
        char current = infixExpression[i];

        if (isOperand(current)) {
            postfixExpression[j++] = current;
        } else if (current == '(') {
            push(stack, current);
        } else if (current == ')') {
            while (stack->top != -1 && stack->items[stack->top] != '(') {
                postfixExpression[j++] = pop(stack);
            }
            if (stack->top != -1 && stack->items[stack->top] != '(') {
                printf("Invalid Expression\n");
                return;
            } else {
                pop(stack);
            }
        } else {
            while (stack->top != -1 && precedence(current) <= precedence(stack->items[stack->top])) {
                postfixExpression[j++] = pop(stack);
            }
            push(stack, current);
        }
    }

    while (stack->top != -1) {
        postfixExpression[j++] = pop(stack);
    }
    postfixExpression[j] = '\0';
}

int main() {
    char infixExpression[MAX_SIZE];
    printf("Enter the infix expression: ");
    fgets(infixExpression, MAX_SIZE, stdin);
    infixExpression[strcspn(infixExpression, "\n")] = '\0'; // Removing trailing newline character

    char postfixExpression[MAX_SIZE];
    infixToPostfix(infixExpression, postfixExpression);

    printf("Postfix Expression: %s\n", postfixExpression);

    return 0;
}

