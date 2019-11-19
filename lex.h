#ifndef PARSE_H 
#define PARSE_H

// abstract syntax tree representing boolean expression.
typedef struct sexp_ast {
  char* data; // string literal
  int type;   // op (0) or atom (1)
  struct sexp_ast* left;
  struct sexp_ast* right;
} sexp_ast;

void free_sexp_ast(sexp_ast* ast);
sexp_ast* make_sexp_ast(void);

sexp_ast* lex(char* input);

#endif
