#ifndef SVEC_H
#define SVEC_H

typedef struct node {
    char* key;
    int type;
} node;

// wrapper for array of char*
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

// print the sv (debugging).
void svec_print(svec* sv);

#endif