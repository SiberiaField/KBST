#include <stdlib.h>
#include <string.h>
#include "pointsVector.h"
#include "../pointData.h"

void initPointVec(pointsVec* vec){
    vec->n = 0;
    vec->cap = 0;
    vec->arr = NULL;
}

void destroyPointVec (pointsVec* vec){
    if(vec == NULL) return;
    vec->n = 0;
    vec->cap = 0;
    free(vec->arr);
    vec->arr = NULL;
}

void pushPointVec (pointsVec* vec, pointData point){
    if(vec == NULL) return;
    if(vec->arr == NULL){
        vec->cap = 1;
        vec->arr = (pointData*)malloc(sizeof(pointData) * vec->cap);
    }
    if(vec->n >= vec->cap){
        vec->cap *= 2;
        vec->arr = (pointData*)realloc(vec->arr, sizeof(pointData) * vec->cap);
    }
    vec->arr[vec->n++] = point;
}

void veccpyPoint(pointsVec* where, pointsVec* from){
    if(where == NULL || from == NULL) return;
    if(where->cap + from->n > where->cap){
        where->cap = where->cap + from->n;
        where->arr = (pointData*)realloc(where->arr, sizeof(pointData) * where->cap);
    }
    memcpy(&where->arr[where->n], from->arr, sizeof(pointData) * from->n);
    where->n += from->n;
}
