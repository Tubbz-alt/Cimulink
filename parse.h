#ifndef PARSE_H 
#define PARSE_H

// abstract syntax tree representing boolean expression.
typedef struct parse_ast {
  char* op;
  struct parse_ast* left;
  struct parse_ast* right;
} parse_ast;

parse_ast parse(char* input);

#endif
