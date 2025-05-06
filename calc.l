%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double result;
char func[10];
%}

%%
[ \t]+                ; // Ignore spaces and tabs

[0-9]+(\.[0-9]+)?     { result = atof(yytext); }
"sin"                 { strcpy(func, "sin"); }
"cos"                 { strcpy(func, "cos"); }
"tan"                 { strcpy(func, "tan"); }
"log"                 { strcpy(func, "log"); }
"exp"                 { strcpy(func, "exp"); }
"sqrt"                { strcpy(func, "sqrt"); }
"^"                   { strcpy(func, "pow"); }
"="                   {
                        if (strcmp(func, "sin") == 0)
                            printf("Result: %lf\n", sin(result));
                        else if (strcmp(func, "cos") == 0)
                            printf("Result: %lf\n", cos(result));
                        else if (strcmp(func, "tan") == 0)
                            printf("Result: %lf\n", tan(result));
                        else if (strcmp(func, "log") == 0)
                            printf("Result: %lf\n", log(result));
                        else if (strcmp(func, "exp") == 0)
                            printf("Result: %lf\n", exp(result));
                        else if (strcmp(func, "sqrt") == 0)
                            printf("Result: %lf\n", sqrt(result));
                        else
                            printf("Result: %lf\n", result); // fallback
                      }
\n                    { printf("Enter expression: "); }
.                     ;
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter expression: ");
    yylex();
    return 0;
}