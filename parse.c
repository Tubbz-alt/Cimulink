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
    return node;
}

void
free_sexp_ast(sexp_ast* ast)
{
    if (ast->arg1) {
        free_sexp_ast(ast->arg0);
        free_sexp_ast(ast->arg1);
        free(ast);
    }
    if (ast->arg0) {
        free_sexp_ast(ast->arg0);
        free(ast);
    }
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

static
void
sexp_print_recur(sexp_ast* ast)
{
    if (ast->arg1) {
        printf("(%s ", ast->op);
        sexp_print_recur(ast->arg0);
        printf(" ");
        sexp_print_recur(ast->arg1);
        printf(")");
    }
    else if (ast->arg0) {
        printf("(%s ", ast->op);
        sexp_print_recur(ast->arg0);
        printf(")");
    }
    else {
        printf("%s", ast->op);
    }
}

// this is just to have a \n at the end of recursive printing
void
sexp_print(sexp_ast* ast)
{
    sexp_print_recur(ast);
    printf("\n");
}

int
sexp_equal(sexp_ast* ast0, sexp_ast* ast1)
{
    if (ast0->arg1 && ast1->arg1) {
        return strcmp(ast0->op, ast1->op) == 0
        && sexp_equal(ast0->arg0, ast1->arg0)
        && sexp_equal(ast0->arg1, ast1->arg1);
    }
    else if (ast0->arg0 && ast1->arg0) {
        return strcmp(ast0->op, ast1->op) == 0
        && sexp_equal(ast0->arg0, ast1->arg0);
    }
    else {
        return strcmp(ast0->op, ast1->op) == 0;
    }
}

sexp_ast*
parse(svec* tokens)
{
    if (tokens->data[0]->type == TYPE_LPAR) {
        svec* expr = svec_slice(tokens, 1, tokens->size - 1);

        // not is special case with asymmetric leaf types.
        if (strcmp(tokens->data[1]->key, "not") == 0) {
            svec* arg0 = svec_slice(expr, 1, expr->size);
            return make_sexp_ast(tokens->data[1]->key, parse(arg0), 0);
        }
        int split = split_args(expr);
        svec* arg0 = svec_slice(expr, 1, split);
        svec* arg1 = svec_slice(expr, split, expr->size);
        sexp_ast* ast = make_sexp_ast(tokens->data[1]->key, parse(arg0), parse(arg1));
        return ast;
    } else {
        sexp_ast* ast = make_sexp_ast(tokens->data[0]->key, 0, 0);
        return ast;
    }
}
