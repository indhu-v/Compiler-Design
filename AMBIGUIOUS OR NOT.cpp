#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUCTIONS 10

typedef struct {
    char nonTerminal;
    char production[20];
} ProductionRule;

ProductionRule productions[MAX_PRODUCTIONS];
int numProductions = 0;

bool isAmbiguous() {
    for (int i = 0; i < numProductions; i++) {
        for (int j = i + 1; j < numProductions; j++) {
            if (productions[i].nonTerminal == productions[j].nonTerminal &&
                strcmp(productions[i].production, productions[j].production) != 0) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);

    printf("Enter the productions (non-terminal followed by production):\n");
    for (int i = 0; i < numProductions; i++) {
        scanf(" %c %s", &productions[i].nonTerminal, productions[i].production);
    }

    if (isAmbiguous()) {
        printf("The grammar is ambiguous.\n");
    } else {
        printf("The grammar is not ambiguous.\n");
    }

    return 0;
}
