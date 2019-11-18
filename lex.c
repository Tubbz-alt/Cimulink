#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isspace
#include <stdio.h>

#include "lex.h"

// wrapper for strcmp
static
int
ischar(char* s, char* cmp)
{

    char c[2] = "x"; // adds null terminator
    c[0] = *s;
    return !strcmp(c, cmp);
}

static
int
isvar(char* s)
{
    // valid variables:
    // {1..8,T, F}
    return ischar(s, "T") || ischar(s, "F") || (isdigit(*s) && 0 < atol(s) && atol(s) < 9);
}

// Read operation from input in bounds {ii, nn}
static
char*
read_op(char* input, int ii, int nn)
{
    char* validops[7] = {"and", "nand", "or", "nor", "xor", "xnor", "not"};
    char* op = malloc(4);
    // this is reading into unverified piece of input char*,
    // only invalid if user input is invalid (ops before args)
    memcpy(op, input, 4);

    for (int ii = 0; ii < 7; ii++) {
        // only check if first two letters are valid
        // (no operators share first two letters)
        // not ideal for input verification
        if (!strncmp(validops[ii], op, 2)) {
            // truncate string to appropriate length
            op[strlen(validops[ii])] = 0;
            return op;
        }
    }

    fprintf(stderr, "Invalid input: %s\n", op);
    exit(1);
}


sexp_ast*
make_sexp_ast(void)
{
    sexp_ast* node = malloc(sizeof(sexp_ast));
    node->left = 0;
    node->right = 0;
    return node;
}

void
free_sexp_ast(sexp_ast* node)
{
    if (node != 0) {
        free_sexp_ast(node->left);
        free_sexp_ast(node->right);
        free(node);
    }
}

char*
printf_sexp_ast(sexp_ast* tree)
{
    char buf[100] = "";
    if (tree) {
        char lstr[8] = "";
        char rstr[8] = "";
        if (tree->left)  { strcat(lstr, tree->left->data); }
        if (tree->right) { strcat(rstr, tree->right->data); }

        strcat(buf, "(");
        strcat(buf, tree->data);
        strcat(buf, " ");
        strcat(buf, lstr);
        strcat(buf, " ");
        strcat(buf, rstr);
        strcat(buf, ")");
    }
    printf("%s\n", buf);
    return buf;
}

sexp_ast*
lex(char* input)
{
    sexp_ast *ast = 0;
    sexp_ast *head = ast;
    int depth = -1; // nested depth of parens

    int nn = strlen(input);
    int ii = 0;      // index in input string
    while (ii < nn) {
        if (isspace(input[ii])) {
            ii++;
            continue;
        }
        if (ischar(&input[ii], "(")) {
            ii++;
            depth++;
            continue;
        }
        if (ischar(&input[ii], ")")) {
            ii++;
            depth--;
            continue;
        }
        if (isvar(&input[ii])) {
            // leaves, non-recursive

            char* var = malloc(sizeof(char));
            strncpy(var, &input[ii], 1);
            var[1] = 0;
            ii++;

            if(!head->left) {
                head->left = make_sexp_ast();
                head->left->data = var;
            } else {
                head->right = make_sexp_ast();
                head->right->data = var;
            }
            continue;
        }
        
        char* op = read_op(&input[ii], ii, nn);
        // printf("%s\n", op);

        if (!ast) {
            ast = make_sexp_ast();
            ast->data = op;
            head = ast;
        }
        ii += strlen(op);
    }
    printf_sexp_ast(ast);
    return ast;
}