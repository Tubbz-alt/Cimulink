#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "token.h"
#include "svec.h"

// compare char s to char* cmp without touching heap
static
int
ischar(char* s, char* cmp)
{

    char c[2] = "x"; // adds null terminator
    c[0] = *s;
    return !strcmp(c, cmp);
}

// compare char s to possible vars
static
int
isvar(char* s)
{
    // valid variables:
    // {1..8,T, F}
    return ischar(s, "T") || ischar(s, "F") || (isdigit(*s) && 0 < atol(s) && atol(s) < 9);
}

// copy nn chars from input buffer at index ii and null terminate
static
char* 
extract_char(char* input, int ii, int nn)
{
    char* val = malloc(sizeof(char));
    strncpy(val, &input[ii], nn);
    val[1] = 0;
    return val;
}

static
node*
make_node(char* key, int type)
{
    node* nn = malloc(sizeof(node));
    nn->key = key;
    nn->type = type;
    return nn;
}

// Read operation from input in bounds {ii, nn}
static
char*
extract_op(char* input, int ii, int nn)
{
    char* validops[6] = {"and", "nand", "or", "nor", "xor", "xnor"};
    char* op = malloc(4);
    // this is reading into unverified piece of input char*,
    // only invalid if user input is invalid (ops before args)
    memcpy(op, input, 4);

    for (int ii = 0; ii < 6; ii++) {
        // only check if first two letters are valid
        // (no operators share first two letters)
        // not ideal for input verification
        if (!strncmp(validops[ii], op, 2)) {
            // truncate string to appropriate length
            op[strlen(validops[ii])] = 0;
            return op;
        }
    }
    fprintf(stderr, "Invalid input: %s\n", op);
    exit(1);
}

svec*
tokenize(char* input)
{
    int nn = strlen(input);
    int ii = 0;      // index in input string
    int depth = 0;    // balanced parens := 0
    svec* tokens = make_svec();
    while (ii < nn) {
        if (isspace(input[ii])) {
            ii++;
            continue;
        }
        
        if (ischar(&input[ii], "(")) {
            char* ex = extract_char(input, ii, 1);
            node* nn = make_node(ex, TYPE_LPAR);
            svec_push_back(tokens, nn);
            ii++;
            depth++;
            continue;
        }

        if (ischar(&input[ii], ")")) {
            char* ex = extract_char(input, ii, 1);
            node* nn = make_node(ex, TYPE_RPAR);
            svec_push_back(tokens, nn);
            ii++;
            depth--;
            continue;
        }

        if (isvar(&input[ii])) {
            char* ex = extract_char(input, ii, 1);
            node* nn = make_node(ex, TYPE_ATOM);
            svec_push_back(tokens, nn);
            ii++;
            continue;
        }
        
        char* op = extract_op(&input[ii], ii, nn);
        node* nn = make_node(op, TYPE_OPER);
        svec_push_back(tokens, nn);
        ii += strlen(op);
    }

    // unbalanced input sexp
    // unbalanced != incorrect lex, but prevents ambiguity
    if (depth) {
        fprintf(stderr, "Unbalanced sexp.\n");
        exit(1);
    }

    return tokens;
}