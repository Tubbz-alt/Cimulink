#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "svec.h"
#include "parse.h"
#include "reduce.h"
#include "zedboard.h"

int
main(int argc, char* argv[])
{
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage:\n\t./booler \"boolexp\" or \"zedboard\"\n");
    exit(1);
  }

  svec* tokens = tokenize(argv[1]);
  sexp_ast* ast = parse(tokens);
  // static char* inputs[8] = {"0","1","0","0","0","0","0","1"};
  // int eval = evaluate(ast, inputs);
  // printf("eval = %d\n", eval);
  if (argc == 3 && strcmp(argv[2], "zedboard") == 0) {
    zedboard(ast);
    return 0;
  }
  ast = reduce(ast);
  sexp_print(ast);
  return 0;
}
