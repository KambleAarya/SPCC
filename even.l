%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+    {
              int num = atoi(yytext);
              if (num % 2 == 0)
                  printf("✔️ %d is Even\n", num);
              else
                  printf("❌ %d is Odd\n", num);
          }

[\n]      { /* ignore newline */ }

.         { /* ignore other characters */ }

%%

int main() {
    printf("Enter numbers (Ctrl+C to exit):\n");
    yylex();
    return 0;
}

int yywrap(void) {
    return 1;
}