#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "svec.h"
#include "parse.h"
#include "eval.h"

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage:\n\t ./booler \"boolexp\"\n");
    exit(1);
  }

  printf("%s\n", argv[1]);
  svec* tokens = tokenize(argv[1]);
  sexp_ast* ast = lex(tokens);
  static char* inputs[8] = {"0","1","0","0","0","0","0","1"};
  int eval = evaluate(ast, inputs);
  printf("eval = %d\n", eval);
  return 0;
}
