#include <stdlib.h>
#include "pointsInRectangle.h"
#include "KBSTnode.h"
#include "pointData.h"
#include "minor_functions/distance.h"
#include "minor_functions/pointsVector.h"

static int inRectangle(KBSTnode* node, int dimension, double* rectangle){
    for(int i = 0; i < dimension; i++)
        if(!(node->point.coords[i] >= rectangle[i * 2] && node->point.coords[i] <= rectangle[i * 2 + 1])) return 0;
    return 1;
}

static int intersectLeft(KBSTnode* node, int dimension, double* rectangle){
    int cmp_coord = node->level % dimension;
    return rectangle[cmp_coord * 2] <= node->point.coords[cmp_coord];
}

static int intersectRight(KBSTnode* node, int dimension, double* rectangle){
    int cmp_coord = node->level % dimension;
    return rectangle[cmp_coord * 2 + 1] >= node->point.coords[cmp_coord];
}

static pointsVec pointsInRectangle_Rec(KBSTnode* node, int dimension, double* rectangle){
    pointsVec res;
    initPointVec(&res);
    if(node == NULL) return res;
    else{
        if(inRectangle(node, dimension, rectangle)) pushPointVec(&res, node->point);
        if(intersectLeft(node, dimension, rectangle)){
            pointsVec leftRes = pointsInRectangle_Rec(node->left, dimension, rectangle);
            veccpyPoint(&res, &leftRes);
            destroyPointVec(&leftRes);
        }
        if(intersectRight(node, dimension, rectangle)){
            pointsVec rightRes = pointsInRectangle_Rec(node->right, dimension, rectangle);
            veccpyPoint(&res, &rightRes);
            destroyPointVec(&rightRes);
        }
        return res;
    }
}

int pointsInRectangle(KBSTnode* node, int dimension, double* rectangle, pointData** points){
    if(node == NULL || rectangle == NULL || dimension < 1 || points == NULL) return 0;
    pointsVec res = pointsInRectangle_Rec(node, dimension, rectangle);
    *points = res.arr;
    return res.n;
}