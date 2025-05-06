#include <stdio.h> 
 
// Define nested macros 
#define SQUARE(x) ((x) * (x)) 
#define SUM_SQUARES(a, b) (SQUARE(a) + SQUARE(b)) 
 
int main() { 
    int a, b; 
 
    printf("Enter two numbers: ");     scanf("%d %d", &a, &b); 
 
    printf("\nNested Macro Call:\n");     printf("SUM_SQUARES(%d, %d)\n", a, b); 
 
    printf("\nExpanded Source Code:\n"); 
    printf("int result = (((%d) * (%d)) + ((%d) * (%d)));\n", a, a, b, b); 
 
    int result = SUM_SQUARES(a, b);     printf("\nComputed Result: %d\n", result); 
 
    return 0; 
}