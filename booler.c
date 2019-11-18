#include <stdio.h>
#include <stdlib.h>

#include "lex.h"

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage:\n\t ./booler \"boolexp\"\n");
    exit(1);
  }

  printf("%s\n", argv[1]);
  sexp_ast* exp = lex(argv[1]);
  return 0;
}
