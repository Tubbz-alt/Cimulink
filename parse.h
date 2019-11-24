#ifndef PARSE_H
#define PARSE_H

#include "svec.h"

// abstract syntax tree representing boolean expression.
typedef struct sexp_ast {
  // operator string ("and", "nand", ...)
  // or variable if both arguments null ("0", "1", ..., "T", "F")
  char* op;
  struct sexp_ast* arg0;
  struct sexp_ast* arg1;
} sexp_ast;

sexp_ast* make_sexp_ast(char* op, sexp_ast* arg0, sexp_ast* arg1);
void free_sexp_ast(sexp_ast* ast);

sexp_ast* parse(svec* input);

int sexp_equal(sexp_ast* ast0, sexp_ast* ast1);
void sexp_print(sexp_ast* ast);

#endif
