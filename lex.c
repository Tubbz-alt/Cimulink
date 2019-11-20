#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isspace
#include <stdio.h>

#include "lex.h"
#include "svec.h"
#include "token.h"

sexp_ast*
make_sexp_op_ast(char* op, sexp_ast* arg0, sexp_ast* arg1)
{
    sexp_op_ast* node = malloc(sizeof(sexp_ast));
    node->op = op;
    node->arg0 = arg0;
    node->arg1 = arg1;
    return (sexp_ast*)node;
}

sexp_ast*
make_sexp_var_ast(char* var)
{
    sexp_var_ast* node = calloc(1, sizeof(sexp_ast));
    node->op = "var";
    node->var = var;
    return (sexp_ast*)node;
}

/*
void
free_sexp_ast(sexp_ast* node)
{
    if (node) {
        if (node->arg0) {
            free_sexp_ast(node->arg0);
        }
        if (node->arg1) {
            free_sexp_ast(node->arg1);
        }
        free(node);
    }
}
*/

/*
char*
print_sexp_ast(sexp_ast* tree)
{
    char buf[1024] = "";
    char lstr[8] = "";
    char rstr[8] = "";

    if (tree->type == 1) { // op 
        if (tree->left)  { strcat(lstr, print_sexp_ast(tree->left)); }
        if (tree->right) { strcat(rstr, print_sexp_ast(tree->right)); }

        strcat(buf, "(");
        strcat(buf, tree->data);
        strcat(buf, " ");
        strcat(buf, lstr);
        strcat(buf, " ");
        strcat(buf, rstr);
        strcat(buf, ")");
    }
    if (tree->type == 1) { // atom

    }
    printf("%s\n", buf);
    return buf;
}
*/

// the index to split args svec.
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
    return -1;
}

sexp_ast*
lex(svec* tokens)
{
    if (tokens->data[0]->type == TYPE_LPAR) {
        svec* expr = svec_slice(tokens, 1, tokens->size - 1);
        int split = split_args(expr);
        svec* arg0 = svec_slice(expr, 1, split);
        svec* arg1 = svec_slice(expr, split, expr->size);
        lex(arg0);
        lex(arg1);
    } else {
        printf("leaf %s\n", tokens->data[0]->key);
    }
}