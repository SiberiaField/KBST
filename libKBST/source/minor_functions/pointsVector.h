#pragma once
#include "../pointData.h"

typedef struct pointsVec {
    pointData* arr;
    int cap;
    int n;
} pointsVec;

void initPointVec(pointsVec* vec);
void destroyPointVec (pointsVec* vec);
void pushPointVec (pointsVec* vec, pointData point);
void veccpyPoint(pointsVec* where, pointsVec* from);