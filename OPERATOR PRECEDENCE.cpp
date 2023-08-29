#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 50

char stack[STACK_SIZE];
int top = -1;
void push(char item) {
    if (top >= STACK_SIZE - 1) {
        printf("Stack Overflow!\n");
        exit(1);
    }
    stack[++top] = item;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow!\n");
        exit(1);
    }
    return stack[top--];
}
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

void operatorPrecedenceParsing(char input[]) {
    int i = 0;
    
    printf("Stack\tInput\tAction\n");
    
    while (input[i] != '\0') {
        if (input[i] == '(') {
            push(input[i]);
            i++;
        } else if (isalnum(input[i])) {
            printf("%s\t", stack);
            printf("%s\t", input + i);
            printf("Shift %c\n", input[i]);
            push(input[i]);
            i++;
        } else if (input[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                printf("%s\t", stack);
                printf("%s\t", input + i);
                printf("Reduce %c\n", pop());
            }
            if (top != -1 && stack[top] == '(') {
                pop(); 
            }
            i++;
        } else { 
            while (top != -1 && precedence(stack[top]) >= precedence(input[i])) {
                printf("%s\t", stack);
                printf("%s\t", input + i);
                printf("Reduce %c\n", pop());
            }
            push(input[i]);
            i++;
        }
    }
    
    while (top != -1) {
        printf("%s\t", stack);
        printf(" \t");
        printf("Reduce %c\n", pop());
    }

    printf("ACCEPTED\n"); 
}

int main() {
    char input[50];
    
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);
    
    operatorPrecedenceParsing(input);
    
    return 0;
}
