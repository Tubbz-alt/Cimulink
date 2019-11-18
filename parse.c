#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "parse.h"

static char* ops[6] = {"and", "nand", "or", "nor", "xor", "xnor"};
static char* vars[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "T", "F"};

// wrapper for strtok
void 
chomp(char* s)
{
    strtok(s, "\n");
}

// wrapper for strcmp
int
ischar(char* s, char* cmp)
{
    char c[2] = "x"; // steal null terminator
    c[0] = *s;
    return !strcmp(c, cmp);
}

int
isvar(char* s)
{
    for (int ii = 0; ii < 10; ii++) {
        if (ischar(vars[ii], s)) {
            return 0;
        }
    }
    return 1;
}

parse_ast
parse(char* input)
{
    int nn = strlen(input);
    int ii = 0;
    while (ii < nn) {
        if (isspace(input[ii])) {
            ii++;
            printf("space\n");
            continue;
        }
        if (ischar(&input[ii],"(")) {
            ii++;
            printf("lparen\n");
            continue;
        }
        if (ischar(&input[ii],")")) {
            ii++;
            printf("rparen\n");
            continue;
        }
        if (isvar(&input[ii])) {
            ii++;
            printf("var\n");
            continue;
        }
    }
}