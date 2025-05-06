#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char prod[MAX][10];
char follow[MAX][10];
char first[MAX][10];
int n;

int findIndex(char nonterm) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nonterm)
            return i;
    }
    return -1;
}

void addFollow(int index, char symbol) {
    if (!strchr(follow[index], symbol)) {
        int len = strlen(follow[index]);
        follow[index][len] = symbol;
        follow[index][len + 1] = '\0';
    }
}

void computeFollow() {
    for (int i = 0; i < n; i++) {
        // Start symbol
        if (i == 0)
            addFollow(i, '$');
    }

    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char *rhs = strchr(prod[i], '-') + 2; // After '->'
            for (int j = 0; rhs[j] != '\0'; j++) {
                if (isupper(rhs[j])) {
                    int B = findIndex(rhs[j]);
                    if (rhs[j + 1] != '\0') {
                        if (!isupper(rhs[j + 1])) {
                            if (!strchr(follow[B], rhs[j + 1])) {
                                addFollow(B, rhs[j + 1]);
                                changed = 1;
                            }
                        } else {
                            int next = findIndex(rhs[j + 1]);
                            for (int k = 0; first[next][k] != '\0'; k++) {
                                if (first[next][k] != 'ε' && !strchr(follow[B], first[next][k])) {
                                    addFollow(B, first[next][k]);
                                    changed = 1;
                                }
                            }
                        }
                    } else {
                        int A = findIndex(prod[i][0]);
                        for (int k = 0; follow[A][k] != '\0'; k++) {
                            if (!strchr(follow[B], follow[A][k])) {
                                addFollow(B, follow[A][k]);
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter productions (ex: E->TR):\n");
    for (int i = 0; i < n; i++) {
        gets(prod[i]);
    }

    printf("Enter FIRST sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c): ", prod[i][0]);
        gets(first[i]);
    }

    computeFollow();

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { ", prod[i][0]);
        for (int j = 0; follow[i][j] != '\0'; j++) {
            printf("%c ", follow[i][j]);
        }
        printf("}\n");
    }

    return 0;
}
