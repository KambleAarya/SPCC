#include <stdio.h>
#include <string.h>
#include <ctype.h>

int tempVarCount = 1;

char* newTemp() {
    static char temp[5];
    sprintf(temp, "t%d", tempVarCount++);
    return temp;
}

void generateTAC(char expr[]) {
    char lhs[10], rhs[50];
    sscanf(expr, "%s = %[^\n]", lhs, rhs); // split into LHS and RHS

    char tokens[10][10]; // store operands/operators
    int tokIndex = 0;

    // Tokenize the RHS
    for (int i = 0; rhs[i]; ) {
        if (isspace(rhs[i])) {
            i++;
        } else if (isalnum(rhs[i])) {
            int j = 0;
            while (isalnum(rhs[i])) {
                tokens[tokIndex][j++] = rhs[i++];
            }
            tokens[tokIndex][j] = '\0';
            tokIndex++;
        } else {
            tokens[tokIndex][0] = rhs[i++];
            tokens[tokIndex][1] = '\0';
            tokIndex++;
        }
    }

    char temp[10], op1[10], op2[10], oper[5];
    int i;

    // First handle *, / operators
    for (i = 0; i < tokIndex; i++) {
        if (strcmp(tokens[i], "*") == 0 || strcmp(tokens[i], "/") == 0) {
            strcpy(op1, tokens[i - 1]);
            strcpy(oper, tokens[i]);
            strcpy(op2, tokens[i + 1]);

            strcpy(temp, newTemp());
            printf("%s = %s %s %s\n", temp, op1, oper, op2);

            strcpy(tokens[i - 1], temp);
            for (int j = i; j < tokIndex - 2; j++) {
                strcpy(tokens[j], tokens[j + 2]);
            }
            tokIndex -= 2;
            i = -1; // restart
        }
    }

    // Then handle +, - operators
    for (i = 0; i < tokIndex; i++) {
        if (strcmp(tokens[i], "+") == 0 || strcmp(tokens[i], "-") == 0) {
            strcpy(op1, tokens[i - 1]);
            strcpy(oper, tokens[i]);
            strcpy(op2, tokens[i + 1]);

            strcpy(temp, newTemp());
            printf("%s = %s %s %s\n", temp, op1, oper, op2);

            strcpy(tokens[i - 1], temp);
            for (int j = i; j < tokIndex - 2; j++) {
                strcpy(tokens[j], tokens[j + 2]);
            }
            tokIndex -= 2;
            i = -1; // restart
        }
    }

    // Final assignment
    printf("%s = %s\n", lhs, tokens[0]);
}

int main() {
    char expr[100];
    printf("Enter an expression (e.g., a = b + c * d): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0; // remove newline

    printf("\nGenerated TAC:\n");
    generateTAC(expr);

    return 0;
}