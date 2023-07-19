#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    int items[MAX_SIZE];
};

void push(struct Stack* stack, int item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->items[++(stack->top)] = item;
}

int pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->items[(stack->top)--];
}

int evaluatePostfixExpression(char* postfixExpression) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    int i, operand1, operand2, result;

    for (i = 0; postfixExpression[i] != '\0'; i++) {
        if (isdigit(postfixExpression[i])) {
            push(stack, postfixExpression[i] - '0');
        } else {
            operand2 = pop(stack);
            operand1 = pop(stack);
            switch (postfixExpression[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid Operator\n");
                    return -1;
            }
            push(stack, result);
        }
    }
    result = pop(stack);
    free(stack);
    return result;
}

int main() {
    char postfixExpression[MAX_SIZE];
    printf("Enter the postfix expression: ");
    fgets(postfixExpression, MAX_SIZE, stdin);
    postfixExpression[strcspn(postfixExpression, "\n")] = '\0'; // Removing trailing newline character

    int result = evaluatePostfixExpression(postfixExpression);
    printf("Result: %d\n", result);

    return 0;
}

