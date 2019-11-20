#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parse.h"
#include "eval.h"

// replace the variable name with its value from input array.
void
input_var(sexp_ast* ast, char* input[])
{
    if (ast->arg0) {
        input_var(ast->arg0, input);
        input_var(ast->arg1, input);
    }
    else {
        ast->op = input[atoi(ast->op)];
    }
}

// evaluate ast with booleans inserted into vars
int
evaluate_inserted(sexp_ast* ast)
{
    if (ast->arg0) {
        if (strcmp(ast->op, "and") == 0) {
            return evaluate_inserted(ast->arg0) && evaluate_inserted(ast->arg1);
        }
        if (strcmp(ast->op, "nand") == 0) {
            return !(evaluate_inserted(ast->arg0) && evaluate_inserted(ast->arg1));
        }
        if (strcmp(ast->op, "or") == 0) {
            return evaluate_inserted(ast->arg0) || evaluate_inserted(ast->arg1);
        }
        if (strcmp(ast->op, "nor") == 0) {
            return !(evaluate_inserted(ast->arg0) || evaluate_inserted(ast->arg1));
        }
        if (strcmp(ast->op, "xor") == 0) {
            int arg0 = evaluate_inserted(ast->arg0);
            int arg1 = evaluate_inserted(ast->arg1);
            return (!arg0 && arg1) || (arg0 && !arg1);
        }
        if (strcmp(ast->op, "xnor") == 0) {
            int arg0 = evaluate_inserted(ast->arg0);
            int arg1 = evaluate_inserted(ast->arg1);
            return (arg0 && arg1) || (!arg0 && !arg1);
        }
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