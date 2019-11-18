#ifndef PARSE_H 
#define PARSE_H

// abstract syntax tree representing boolean expression.
typedef struct bool_ast {
  char* op;
  struct bool_ast* left;
  struct bool_ast* right;
} bool_ast;

bool_ast lex(char* input);

#endif
