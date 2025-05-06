%{
#include <stdio.h>
#include <stdlib.h>

long long factorial(int n) {
    if (n < 0) return -1; // Error case
    long long result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

int number = 0;
%}

%%
[ \t]+           ; // Ignore whitespaces

[0-9]+           { number = atoi(yytext); }

"fact"           {
                    if (number < 0)
                        printf("Factorial is not defined for negative numbers.\n");
                    else
                        printf("Factorial of %d is %lld\n", number, factorial(number));
                 }

\n               { printf("Enter input: "); }

.                ; // Ignore other characters
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter input: ");
    yylex();
    return 0;
}