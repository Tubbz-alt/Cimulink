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

sexp_ast*
lex(svec* tokens)
{
    for (int ii = 0; ii < tokens->size; ii++) {
        
    }
}