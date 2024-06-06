#pragma once
typedef struct doubleVec {
    double* arr;
    int cap;
    int n;
} doubleVec;

void initDblVec(doubleVec* vec);
void destroyDblVec (doubleVec* vec);
void pushDblVec (doubleVec* vec, double value);
void veccpyDbl(doubleVec* where, doubleVec* from);