#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generateAssembly(char *tacLine) {
    char result[10], op1[10], op2[10], op;
    
    if (sscanf(tacLine, "%s = %s %c %s", result, op1, &op, op2) == 4) {
        printf("MOV %s, R1\n", op1);

        switch(op) {
            case '+': printf("ADD %s, R1\n", op2); break;
            case '-': printf("SUB %s, R1\n", op2); break;
            case '*': printf("MUL %s, R1\n", op2); break;
            case '/': printf("DIV %s, R1\n", op2); break;
            default: printf("; Unsupported operator: %c\n", op); break;
        }

        printf("MOV R1, %s\n", result);
    } 
    else if (sscanf(tacLine, "%s = %s", result, op1) == 2) {
        // Simple assignment
        printf("MOV %s, R1\n", op1);
        printf("MOV R1, %s\n", result);
    } 
    else {
        printf("; Unsupported TAC: %s\n", tacLine);
    }
}

int main() {
    char tac[100][50];
    int n;

    printf("Enter number of TAC instructions: ");
    scanf("%d", &n);
    getchar();  // Consume newline

    printf("Enter TAC instructions (e.g., t1 = a + b):\n");
    for (int i = 0; i < n; i++) {
        fgets(tac[i], sizeof(tac[i]), stdin);
        tac[i][strcspn(tac[i], "\n")] = 0; // Remove newline
    }

    printf("\nGenerated Assembly Code:\n");
    for (int i = 0; i < n; i++) {
        generateAssembly(tac[i]);
    }

    return 0;
}