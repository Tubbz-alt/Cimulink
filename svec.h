#ifndef SVEC_H
#define SVEC_H

#define TYPE_OPER 0
#define TYPE_ATOM 1
#define TYPE_LPAR 2
#define TYPE_RPAR 3

typedef struct node {
    char* key;
    int type;
} node;

// wrapper for array of node*
typedef struct svec {
    int size;
    int capacity;
    node** data;
} svec;

// allocate memory (size 0, capacity 2)
svec* make_svec(void);

// release memory sv uses
void  free_svec(svec* sv);

// get the value in sv at index ii
node* svec_get(svec* sv, int ii);

// put item at index ii in sv
void svec_put(svec* sv, int ii, node* item);

// append item onto the end of sv
void svec_push_back(svec* sv, node* item);

// sub-svec from indeces ii to jj
svec* svec_sub(svec* sv, int ii, int jj);

// print the sv (debugging).
void svec_print(svec* sv);

#endif