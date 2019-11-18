#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lex.h"

// wrapper for trtok
void 
chomp(char* s)
{
    strtok(s, "\n");
}

// wrapper for strcmp
int
ischar(char* s, char* cmp)
{

    char c[2] = "x";
    c[0] = *s;
    return !strcmp(c, cmp);
}

int
islparen(char* s)
{
    return ischar(s, "(");
}

int
isrparen(char* s)
{
    return ischar(s, ")");
}

int
isvar(char* s)
{
    // valid variables:
    // {1..8,T, F}
    return ischar(s, "T") || ischar(s, "F") || (isdigit(*s) && 0 < atol(s) && atol(s) < 9);
}

// Read operation from input in bounds {ii, nn}
char*
read_op(char* input, int ii, int nn)
{
    if (nn - ii < 3) {
        perror("Invalid input.\n");
        exit(1);
    }  
}

bool_ast
lex(char* input)
{
    int nn = strlen(input);
    int ii = 0;
    while (ii < nn) {
        // space characters, pass
        if (isspace(input[ii])) {
            ii++;
            printf("space\n");
            continue;
        }
        // left paren control
        if (islparen(&input[ii])) {
            ii++;
            printf("lparen\n");
            continue;
        }
        // right paren control
        if (isrparen(&input[ii])) {
            ii++;
            printf("rparen\n");
            continue;
        }
        // variable control (leaves)
        if (isvar(&input[ii])) {
            ii++;
            printf("var\n");
            continue;
        }
        
        // char* op = read_op(&input[ii], ii, nn);
        // printf("%s\n", op);
    }
}