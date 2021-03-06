#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "reduce.h"

// X + T = X
// X * F = X
static
sexp_ast*
identity(sexp_ast* ast)
{
    if (strcmp(ast->op, "and") == 0
    && strcmp(ast->arg1->op, "T") == 0) {
        return ast->arg0;
    }
    if (strcmp(ast->op, "or") == 0
    && strcmp(ast->arg1->op, "F") == 0) {
        return ast->arg0;
    }
    return ast;
}

// X + T = T
// X * F = F
static
sexp_ast*
null(sexp_ast* ast)
{
    if (strcmp(ast->op, "and") == 0
    && strcmp(ast->arg1->op, "F") == 0) {
        // free_sexp_ast(ast);
        return make_sexp_ast("F", 0, 0);
    }
    if (strcmp(ast->op, "or") == 0
    && strcmp(ast->arg1->op, "T") == 0) {
        return make_sexp_ast("T", 0, 0);
    }
    return ast; 
}


// X + X = X
// X * X = X
static
sexp_ast*
idempotency(sexp_ast* ast)
{
    if (strcmp(ast->op, "and") == 0 
    && sexp_equal(ast->arg0, ast->arg1)) {
        return ast->arg0;
    }
    if (strcmp(ast->op, "or") == 0 
    && sexp_equal(ast->arg0, ast->arg1)) {
        return ast->arg0;
    }
    return ast;
}

// (X')' = X
static
sexp_ast*
involution(sexp_ast* ast)
{
    if (strcmp(ast->op, "not") == 0 
    && strcmp(ast->arg0->op, "not") == 0) {
        return ast->arg0->arg0;
    }
    return ast;
}

// X + X' = T
// X * X' = F
static
sexp_ast*
complementarity(sexp_ast* ast)
{
    if (strcmp(ast->op, "and") == 0 
    && strcmp(ast->arg1->op, "not") == 0
    && sexp_equal(ast->arg0, ast->arg1->arg0)) {
        // free_sexp_ast(ast);
        return make_sexp_ast("F", 0, 0);
    }
    if (strcmp(ast->op, "or") == 0 
    && strcmp(ast->arg1->op, "not") == 0
    && sexp_equal(ast->arg0, ast->arg1->arg0)) {
        // free_sexp_ast(ast);
        return make_sexp_ast("T", 0, 0);
    }
    return ast;
}

// op(X,Y) == op(Y,X)
// every op but not is commutative.
static
sexp_ast*
commutativity(sexp_ast* ast)
{
    if (strcmp(ast->op, "not") != 0) {
        sexp_ast* tmp = ast->arg0;
        ast->arg0 = ast->arg1;
        ast->arg1 = tmp;
        return ast;
    }
    return ast;
}

// op(X,op(Y,Z)) == op(Y,op(X,Z))
// every op but not is associative.
static
sexp_ast*
associativity(sexp_ast* ast)
{
    if (strcmp(ast->op, "not") != 0
    && (strcmp(ast->arg1->op, ast->op) == 0)) {
        sexp_ast* tmp =  ast->arg1->arg0;
        ast->arg1->arg0 = ast->arg0;
        ast->arg0 = tmp;
        return ast;
    }
    return ast;
}

// (A * B) + (A * C) = A * (B + C)
// (A + B) * (A + C) = A + (B * C)
static
sexp_ast*
distributivity(sexp_ast* ast)
{
    if (strcmp(ast->op, "and") == 0
    && strcmp(ast->arg0->op, "or") == 0
    && strcmp(ast->arg1->op, "or") == 0
    && sexp_equal(ast->arg0->arg0, ast->arg1->arg0)) {
        // free_sexp_ast(ast);
        return make_sexp_ast("or", ast->arg0->arg0, make_sexp_ast("and", ast->arg0->arg1, ast->arg1->arg1));
    }
    if (strcmp(ast->op, "or") == 0
    && strcmp(ast->arg0->op, "and") == 0
    && strcmp(ast->arg1->op, "and") == 0
    && sexp_equal(ast->arg0->arg0, ast->arg1->arg0)) {
        // free_sexp_ast(ast);
        return make_sexp_ast("and", ast->arg0->arg0, make_sexp_ast("or", ast->arg0->arg1, ast->arg1->arg1));
    }
    return ast;
}

static
sexp_ast*
tryall(sexp_ast* ast)
{
    ast = identity(ast);
    ast = null(ast);
    ast = idempotency(ast);
    ast = involution(ast);
    ast = complementarity(ast);
    // ast = commutativity(ast);
    // ast = associativity(ast);
    ast = distributivity(ast);
    return ast;
}

static
sexp_ast*
reduce_recur(sexp_ast* ast)
{

    ast = tryall(ast);
    if (ast->arg1) {
        ast->arg0 = reduce_recur(ast->arg0);
        ast->arg1 = reduce_recur(ast->arg1);
    }
    else if (ast->arg0) {
        ast->arg0 = reduce_recur(ast->arg0);
    }
    return ast;
}

sexp_ast*
reduce(sexp_ast* ast)
{
    sexp_ast* comp = make_sexp_ast(ast->op, ast->arg0, ast->arg1);
    ast = reduce_recur(ast);
    if (!sexp_equal(ast, comp)) {
        ast = reduce(ast);
    }
    return ast;
}