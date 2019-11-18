#include <stdio.h>
#include <stdlib.h>

#include "parse.h"

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    printf("Usage:\n\t ./booler \"boolexp\"\n");
    exit(1);
  }

  printf("%s\n", argv[1]);
  parse_ast exp = parse(argv[1]);
  return 0;
}
