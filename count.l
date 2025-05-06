%{
#include <stdio.h>
#include <ctype.h>

int char_count = 0;
int word_count = 0;
int sentence_count = 0;
int line_count = 0;
int tab_count = 0;
int number_count = 0;

int in_word = 0;
%}

%%
[ \t]+        {
                char_count += yyleng;
                if (yytext[0] == '\t')
                    tab_count++;
                in_word = 0;
              }

[0-9]+        {
                number_count++;
                char_count += yyleng;
                in_word = 1;
              }

[A-Za-z]+     {
                char_count += yyleng;
                if (!in_word) {
                    word_count++;
                    in_word = 1;
                }
              }

[.!?]         {
                sentence_count++;
                char_count++;
                in_word = 0;
              }

\n            {
                line_count++;
                char_count++;
                in_word = 0;
              }

.             {
                char_count++;
                in_word = 0;
              }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter text (Ctrl+D to end input on Linux/Mac, Ctrl+Z on Windows):\n");
    yylex();
    printf("\n========= STATISTICS =========\n");
    printf("Characters     : %d\n", char_count);
    printf("Words          : %d\n", word_count);
    printf("Sentences      : %d\n", sentence_count);
    printf("Lines          : %d\n", line_count);
    printf("Tabs           : %d\n", tab_count);
    printf("Numbers        : %d\n", number_count);
    return 0;
}