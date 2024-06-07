#pragma once
#include "../KBSTnode.h"
#include "../pointData.h"

typedef struct priQ {
    double* dists;
    pointData* points;
    int cap;
    int n;
} priQ;

void initPriQ(priQ* Q, int cap);  
double topPriQ(priQ* Q, pointData* point);
double peekPriQ(priQ* Q, pointData* point);
int insertPriQ(priQ* Q, double dist, pointData* point);