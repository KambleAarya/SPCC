%{
#include <stdio.h>
#include <string.h>

// C keywords to exclude from identifiers
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while", "inline", "restrict", "_Bool", "_Complex", "_Imaginary"
};

int is_keyword(const char* str) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*    {
                            if (!is_keyword(yytext))
                                printf("Identifier: %s\n", yytext);
                         }

.|\n                      ; // Ignore everything else

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter C code (Ctrl+D to end input on Linux/Mac, Ctrl+Z on Windows):\n");
    yylex();
    return 0;
}