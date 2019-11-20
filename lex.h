#ifndef PARSE_H 
#define PARSE_H

#include "svec.h"

// abstract syntax tree representing boolean expression.
// doubly linked.
typedef struct sexp_ast {
  // operator string ("and", "nand", ...)
  // in case or a var, "var"
  char* op;
} sexp_ast;

typedef struct sexp_op_ast {
  char* op;
  struct sexp_ast* arg0;
  struct sexp_ast* arg1;
} sexp_op_ast;

typedef struct sexp_var_ast {
  char* op;
  char* var;
} sexp_var_ast;

sexp_ast* make_sexp_op_ast(char* op, sexp_ast* arg0, sexp_ast* arg1);
sexp_ast* make_sexp_var_ast(char* val);
void free_sexp_ast(sexp_ast* ast);

sexp_ast* lex(svec* input);

#endif
