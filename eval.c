#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parse.h"
#include "eval.h"

// replace the variable name with its value from input array.
static
void
input_var(sexp_ast* ast, char* input[])
{
    if (ast->arg1) {
        input_var(ast->arg0, input);
        input_var(ast->arg1, input);
    }
    else if (ast->arg0) {
        input_var(ast->arg0, input);
    }
    else {
        if (strcmp(ast->op, "T") == 0) { ast->op = "1"; }
        if (strcmp(ast->op, "F") == 0) { ast->op = "0"; }
        ast->op = input[atoi(ast->op)];
    }
}

// evaluate ast with booleans inserted into vars
static
int
evaluate_inserted(sexp_ast* ast)
{
    if (ast->arg1) {
        int arg0 = evaluate_inserted(ast->arg0);
        int arg1 = evaluate_inserted(ast->arg1);
        // a switch statement would be nice, but apparently not possible
        if (strcmp(ast->op, "and") == 0) {
            return arg0 && arg1;
        }
        if (strcmp(ast->op, "or") == 0) {
            return arg0 || arg1;
        }
        if (strcmp(ast->op, "xor") == 0) {
            return (!arg0 && arg1) || (arg0 && !arg1);
        }
        fprintf(stderr, "corrupted operator: %s\n", ast->op);
        exit(1);
    }
    // has arg0, not arg1 -- "not"
    else if (ast->arg0) {
        if (strcmp(ast->op, "not") == 0) {
            return !evaluate_inserted(ast->arg0);
        }
        fprintf(stderr, "corrupted operator: %s\n", ast->op);
        exit(1);
    }
    else {
        return atoi(ast->op);
    }
}

// evaluate ast with variables set as input
int
evaluate(sexp_ast* ast, char* input[])
{
    input_var(ast, input);
    return evaluate_inserted(ast);
}