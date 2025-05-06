#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char prod[MAX][10];
char first[MAX][10];
int n;

int isNonTerminal(char symbol) {
    return isupper(symbol);
}

void addToFirst(int index, char symbol) {
    if (!strchr(first[index], symbol)) {
        int len = strlen(first[index]);
        first[index][len] = symbol;
        first[index][len + 1] = '\0';
    }
}

void findFirst(int index) {
    char nt = prod[index][0];

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nt) {
            char *rhs = strchr(prod[i], '-') + 2;
            if (!isNonTerminal(rhs[0])) {
                addToFirst(index, rhs[0]);
            } else {
                int k = 0;
                while (rhs[k] != '\0') {
                    if (rhs[k] == nt) break;
                    int next = -1;
                    for (int j = 0; j < n; j++) {
                        if (prod[j][0] == rhs[k]) {
                            next = j;
                            break;
                        }
                    }
                    if (next == -1) break;

                    if (strlen(first[next]) == 0)
                        findFirst(next);

                    for (int f = 0; first[next][f] != '\0'; f++) {
                        if (first[next][f] != 'ε')
                            addToFirst(index, first[next][f]);
                    }

                    // If ε in FIRST(Yi), continue to Yi+1
                    if (!strchr(first[next], 'ε'))
                        break;
                    else
                        k++;
                }

                if (rhs[k] == '\0')
                    addToFirst(index, 'ε');
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter productions (ex: E->TR):\n");
    for (int i = 0; i < n; i++) {
        gets(prod[i]);
        first[i][0] = '\0';
    }

    for (int i = 0; i < n; i++) {
        findFirst(i);
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = { ", prod[i][0]);
        for (int j = 0; first[i][j] != '\0'; j++) {
            printf("%c ", first[i][j]);
        }
        printf("}\n");
    }

    return 0;
}
