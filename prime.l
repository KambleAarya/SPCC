%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Helper function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}
%}

%%

[0-9]+    {
              int num = atoi(yytext);
              if (is_prime(num))
                  printf("✔️ %d is a Prime number\n", num);
              else
                  printf("❌ %d is NOT a Prime number\n", num);
          }

[\n]      {/* ignore newline */}

.         {/* ignore other characters */}

%%

int main() {
    printf("Enter numbers (Ctrl+C to exit):\n");
    yylex();
    return 0;
}

int yywrap(void) {
    return 1;
}