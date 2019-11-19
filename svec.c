#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "svec.h"

svec*
make_svec(void)
{
    svec* sv = malloc(sizeof(svec));
    sv->size = 0;
    sv->capacity = 2;
    sv->data = calloc(sv->capacity, sizeof(node));
    return sv;
}

void
free_svec(svec* sv)
{
    for (int ii = 0; ii < sv->size; ++ii) {
        free(sv->data[ii]);
    }
    free(sv->data); // pair to sv->data malloc()
    free(sv);       // pair to sv malloc()
}

node*
svec_get(svec* sv, int ii)
{
    assert(ii >= 0 && ii < sv->size);
    return sv->data[ii];
}

void
svec_put(svec* sv, int ii, node* item)
{
    assert(ii >= 0 && ii < sv->size);
    sv->data[ii] = item;
}

void
svec_push_back(svec* sv, node* item)
{
    int ii = sv->size;
    if (sv->size == sv->capacity) {
        sv->capacity *= 2;
        sv->data = realloc(sv->data, sv->capacity * sizeof(node));
    }
    
    sv->size = ii + 1;
    svec_put(sv, ii, item);
}

void
svec_print(svec* sv)
{
    for (int ii = 0; ii < sv->size; ++ii) {
        printf("%s ", sv->data[ii]->key);
    }
    printf("\n");
}
