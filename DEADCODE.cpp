#include <stdio.h>
#include <string.h>

typedef struct {
    char statement[50];
    int isAlive;
} Statement;

Statement statements[50];
int nextStatement = 0;

void addStatement(char statement[]) {
    Statement newStatement;
    strcpy(newStatement.statement, statement);
    newStatement.isAlive = 1;
    statements[nextStatement++] = newStatement;
}

int main() {
    addStatement("x = 5;");
    addStatement("y = x + 3;");
    addStatement("z = x * y;");
    addStatement("x = z - 2;");
    addStatement("y = 10;");

    printf("Original Statements:\n");
    for (int i = 0; i < nextStatement; i++) {
        printf("%s\n", statements[i].statement);
    }

    // Identify and eliminate dead code
    for (int i = nextStatement - 1; i >= 0; i--) {
        if (!strstr(statements[i].statement, "=")) {
            statements[i].isAlive = 0;
        } else {
            char* var = strtok(statements[i].statement, " =;");
            while (var != NULL) {
                for (int j = i + 1; j < nextStatement; j++) {
                    if (strstr(statements[j].statement, var)) {
                        statements[i].isAlive = 1;
                        break;
                    }
                }
                var = strtok(NULL, " =;");
            }
        }
    }

    printf("\nAfter Dead Code Elimination:\n");
    for (int i = 0; i < nextStatement; i++) {
        if (statements[i].isAlive) {
            printf("%s\n", statements[i].statement);
        }
    }

    return 0;
}

