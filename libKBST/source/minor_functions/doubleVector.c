#include <stdlib.h>
#include <string.h>
#include "doubleVector.h"

void initDblVec(doubleVec* vec){
    vec->n = 0;
    vec->cap = 0;
    vec->arr = NULL;
}

void destroyDblVec (doubleVec* vec){
    if(vec == NULL) return;
    vec->n = 0;
    vec->cap = 0;
    free(vec->arr);
    vec->arr = NULL;
}

void pushDblVec (doubleVec* vec, double value){
    if(vec == NULL) return;
    if(vec->arr == NULL){
        vec->cap = 1;
        vec->arr = (double*)malloc(sizeof(double) * vec->cap);
    }
    if(vec->n >= vec->cap){
        vec->cap *= 2;
        vec->arr = (double*)realloc(vec->arr, sizeof(double) * vec->cap);
    }
    vec->arr[vec->n++] = value;
}

void veccpyDbl(doubleVec* where, doubleVec* from){
    if(where == NULL || from == NULL) return;
    if(where->cap + from->n > where->cap){
        where->cap = where->cap + from->n;
        where->arr = (double*)realloc(where->arr, sizeof(double) * where->cap);
    }
    memcpy(&where->arr[where->n], from->arr, sizeof(double) * from->n);
    where->n += from->n;
}
