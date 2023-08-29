#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Triple;

Triple triples[50];
int nextTriple = 0;

void generateTriple(char op, char arg1[], char arg2[], char result[]) {
    Triple newTriple;
    newTriple.op = op;
    strcpy(newTriple.arg1, arg1);
    strcpy(newTriple.arg2, arg2);
    strcpy(newTriple.result, result);
    triples[nextTriple++] = newTriple;
}

int main() {
    char expr[100];
    printf("Enter a simple expression: ");
    scanf("%s", expr);

    char temp[10];
    int tempCount = 0;
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            temp[tempCount] = '\0';
            generateTriple(expr[i], temp, "", "");
            tempCount = 0;
        } else {
            temp[tempCount++] = expr[i];
        }
    }
    temp[tempCount] = '\0';
    generateTriple('=', temp, "", "result");

    printf("Generated Triples:\n");
    printf("Op\tArg1\tArg2\tResult\n");
    for (int i = 0; i < nextTriple; i++) {
        printf("%c\t%s\t%s\t%s\n", triples[i].op, triples[i].arg1, triples[i].arg2, triples[i].result);
    }

    return 0;
}
