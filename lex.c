#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isspace
#include <stdio.h>

#include "lex.h"
#include "svec.h"
#include "token.h"

sexp_ast*
make_sexp_ast(void)
{
    sexp_ast* node = malloc(sizeof(sexp_ast));
    node->left = 0;
    node->right = 0;
    node->up = 0;
    return node;
}

void
free_sexp_ast(sexp_ast* node)
{
    if (node) {
        free_sexp_ast(node->left);
        free_sexp_ast(node->right);
        free(node);
    }
}

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
        if (args->data[ii]->type == TYPE_LPAR) { balance++; }
        if (args->data[ii]->type == TYPE_RPAR) { balance--; }
        if (balance == 0) { return ii + 1; }
    }
    return -1;
}

sexp_ast*
lex(svec* tokens)
{
    sexp_ast* ast = make_sexp_ast();
    sexp_ast* head = ast;

    switch (tokens->data[0]->type) {
    case TYPE_LPAR: {
        svec *sub_sexp = svec_sub(tokens, 1, tokens->size - 1);

        // set operator

        break;
    }
    case TYPE_OPER: {
        svec *args = svec_sub(tokens, 1, tokens->size);
        int split = split_args(args) + 1;
        svec* arg1 = svec_sub(tokens, 0, split);
        svec* arg2 = svec_sub(tokens, split, tokens->size);

        // recur down each branch

        free_svec(args);
        break;
    }
    case TYPE_ATOM: {

        // base case

        break;
    }
    default:
        fprintf(stderr, "Unkown node tag: %s\n", tokens->data[0]->key);
    }

    return ast;
}