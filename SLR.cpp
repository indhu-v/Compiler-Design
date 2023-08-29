#include <stdio.h>
#include <string.h>

// Grammar productions
char *productions[] = {
    "E -> E + T",
    "E -> T",
    "T -> int"
};

int numProductions = sizeof(productions) / sizeof(productions[0]);

// Action table and goto table (using simple arrays for demonstration)
int actionTable[4][3] = {
    { 0, 0, 0 }, // Placeholder values, replace with actual values
    { 0, 0, 0 }, // Placeholder values, replace with actual values
    { 0, 0, 0 }, // Placeholder values, replace with actual values
    { 0, 0, 0 }  // Placeholder values, replace with actual values
};

int gotoTable[4][2] = {
    { 0, 0 }, // Placeholder values, replace with actual values
    { 0, 0 }, // Placeholder values, replace with actual values
    { 0, 0 }, // Placeholder values, replace with actual values
    { 0, 0 }  // Placeholder values, replace with actual values
};

// Stack for LR parsing
int stack[1000];
int top = -1;

void push(int state) {
    stack[++top] = state;
}

int pop() {
    return stack[top--];
}

int main() {
    char input[100];
    int state = 0;
    int i = 0;

    printf("Enter input: ");
    scanf("%s", input);

    push(0);

    // Perform SLR parsing
    while (i < strlen(input)) {
        int symbol = input[i] - '0'; // Assuming 'int' is the only terminal symbol

        int action = actionTable[state][symbol];

        if (action == 0) {
            printf("Error: No action found for state %d and symbol %d\n", state, symbol);
            return 1;
        }

        if (action > 0) {
            push(action);
            i++;
        } else if (action < 0) {
            int productionIndex = -action;
            int numSymbols = strlen(productions[productionIndex - 1]) - 5; // Length of "E -> " or "T -> "
            while (numSymbols > 0) {
                pop();
                numSymbols--;
            }
            int nonTerminal = productions[productionIndex - 1][0] - 'A'; // Assuming non-terminals are capital letters
            state = gotoTable[stack[top]][nonTerminal];
            push(state);
        }
    }

    if (stack[top] == 3 && i == strlen(input)) {
        printf("Input successfully parsed!\n");
    } else {
        printf("Parsing failed!\n");
    }

    return 0;
}

