#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "reduce.h"

// (X')' = X
void
involution(sexp_ast* ast)
{
    if (strcmp(ast->op, "not") == 0 && strcmp(ast->arg0->op, "not") == 0) {
        ast = ast->arg0->arg0;
    }
}

void
reduce(sexp_ast* ast)
{
    involution(ast);
    int equal = sexp_equal(ast->arg0, ast->arg1);
    printf("equal? %d\n", equal);
}