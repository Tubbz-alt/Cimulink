#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "svec.h"
#include "lex.h"

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
  sexp_print(ast);

  return 0;
}
