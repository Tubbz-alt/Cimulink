#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>

#include "zedboard.h"
#include "eval.h"
#include "token.h"

void
zedboard(sexp_ast* ast)
{
    int input_fd = open("data.dat", O_CREAT | O_RDWR, 0644);
    assert(input_fd);
    char* input = (char*)mmap(0, 8 * sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, input_fd, 0);
    assert(input != MAP_FAILED);

    while (1) {
        
    }
}