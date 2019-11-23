#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isspace
#include <stdio.h>

#include "parse.h"
#include "svec.h"
#include "token.h"

sexp_ast*
make_sexp_ast(char* op, sexp_ast* arg0, sexp_ast* arg1)
{
    sexp_ast* node = malloc(sizeof(sexp_ast));
    node->op = op;
    node->arg0 = arg0;
    node->arg1 = arg1;
    return (sexp_ast*)node;
}

// the index to split args svec.
static
int
split_args(svec* args)
{
    int balance = 0;
    for (int ii = 0; ii < args->size; ii++) {
        if (args->data[ii]->type == TYPE_OPER) { continue; }
        if (args->data[ii]->type == TYPE_LPAR) { balance++; }
        if (args->data[ii]->type == TYPE_RPAR) { balance--; }
        if (balance == 0) { return ii + 1; }
    }
    fprintf(stderr, "Expected valid expression, found:\n");
    svec_print(args);
    exit(1);
}

void
sexp_print(sexp_ast* ast)
{
    if (ast->arg1) {
        printf("head %s\n", ast->op);
        sexp_print(ast->arg0);
        sexp_print(ast->arg1);
    }
    else if (ast->arg0) {
        printf("head %s\n", ast->op);
        sexp_print(ast->arg0);
    }
    else {
        printf("leaf %s\n", ast->op);
    }
}

sexp_ast*
lex(svec* tokens)
{
    if (tokens->data[0]->type == TYPE_LPAR) {
        svec* expr = svec_slice(tokens, 1, tokens->size - 1);

        // not is special case with asymmetric leaf types.
        if (strcmp(tokens->data[1]->key, "not") == 0) {
            svec* arg0 = svec_slice(expr, 1, expr->size);
            return make_sexp_ast(tokens->data[1]->key, lex(arg0), 0);
        }
        int split = split_args(expr);
        svec* arg0 = svec_slice(expr, 1, split);
        svec* arg1 = svec_slice(expr, split, expr->size);
        sexp_ast* ast = make_sexp_ast(tokens->data[1]->key, lex(arg0), lex(arg1));
        return ast;
    } else {
        sexp_ast* ast = make_sexp_ast(tokens->data[0]->key, 0, 0);
        return ast;
    }
}
