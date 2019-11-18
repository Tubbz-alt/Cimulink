#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isspace
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
    char* validops[7] = {"and", "nand", "or", "nor", "xor", "xnor", "not"};
    char* op = malloc(4);
    memcpy(op, input, 4);

    for (int ii = 0; ii < 7; ii++) {
        if (!strncmp(validops[ii], op, 2)) {
            // truncate string to appropriate length
            op[strlen(validops[ii])] = 0;
            return op;
        }
    }

    printf("Invalid operator: %s\n", op);
    exit(1);
}

bool_ast
lex(char* input)
{
    int nn = strlen(input);
    int ii = 0;      // index in input string
    int balance = 0; // balanced parens := 0
    while (ii < nn) {
        if (isspace(input[ii])) {
            ii++;
            continue;
        }
        if (islparen(&input[ii])) {
            ii++;
            printf("lparen\n");
            balance++;
            continue;
        }
        if (isrparen(&input[ii])) {
            ii++;
            printf("rparen\n");
            balance--;
            continue;
        }
        if (isvar(&input[ii])) {
            ii++;
            printf("var\n");
            continue;
        }
        
        char* op = read_op(&input[ii], ii, nn);
        printf("%s\n", op);
        ii += strlen(op);
    }
}