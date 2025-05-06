%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int op=0;
double a =0, b=0;
void digi();
%}

%%
[0-9]+(\.[0-9]+)? { digi(); }
[+]         { op=1; }
[-]         { op=2; }
[*]         { op=3; }
[/]         { op=4; }
[sin]         { op=5; }
[\(]           { op=6; }
[\)]           { op=7; }
[\=]           { op=8; }
[\n]          { printf("\nThe Answer: %lf\n", a);}
%%
void digi(){
        if(op==0){
                a = atof(yytext);
        }
        else {
                b = atof(yytext);
                switch(op){
                        case 1: a = a + b; break;
                        case 2: a = a - b; break;
                        case 3: a = a * b; break;
                        case 4: if(b!=0)
                                a = a / b;
                                else{
                                        printf("Error\n");
                                        a = 0;
                                }
                                break;
                        case 5: a = atof(yytext);
                                a = sin(a * M_PI / 180.0);
                                break;
                        case 6: break;
                        case 7: break;
                        case 8: printf("Result: %lf\n", a); break;
                }
                op = 0;
        }
}

int main(int argc, char argv[]){
        printf("Enter an expression: \n");
        yylex();
        return 0;
}