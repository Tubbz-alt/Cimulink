#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "svec.h"

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage:\n\t ./booler \"boolexp\"\n");
    exit(1);
  }

  printf("%s\n", argv[1]);
  svec* tokens = tokenize(argv[1]);

  return 0;
}
