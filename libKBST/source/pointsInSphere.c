#include <stdlib.h>
#include "pointsInSphere.h"
#include "KBSTnode.h"
#include "pointData.h"
#include "minor_functions/distance.h"
#include "minor_functions/pointsVector.h"
#include "minor_functions/doubleVector.h"

static void rescpy(doubleVec* A_dists, pointsVec* A_points, doubleVec* B_dists, pointsVec* B_points){
    veccpyPoint(A_points, B_points);
    destroyPointVec(B_points);
    veccpyDbl(A_dists, B_dists);
    destroyDblVec(B_dists);
}

static void pointsInSphere_Rec(KBSTnode* node, int dimension, double* center, double radius, pointsVec* points, doubleVec* dists){
    pointsVec res_points;
    doubleVec res_dists;
    initPointVec(&res_points);
    initDblVec(&res_dists);
    if(node == NULL){
        *points = res_points;
        *dists = res_dists;
    }
    else{
        double dist = distance(node->point.coords, center, dimension);
        if(dist <= radius) {
            pushPointVec(&res_points, node->point);
            pushDblVec(&res_dists, dist);
        }

        int cmp_coord = node->level % dimension;
        KBSTnode* closeBranch = node->right;
        KBSTnode* farBranch = node->left;
        if(center[cmp_coord] < node->point.coords[cmp_coord]){
            closeBranch = node->left;
            farBranch = node->right;
        }

        pointsVec closeRes_points;
        doubleVec closeRes_dists;
        pointsInSphere_Rec(closeBranch, dimension, center, radius, &closeRes_points, &closeRes_dists);
        rescpy(&res_dists, &res_points, &closeRes_dists, &closeRes_points);

        if(splitDistance(node, center, dimension) < radius){
            pointsVec farRes_points;
            doubleVec farRes_dists;
            pointsInSphere_Rec(farBranch, dimension, center, radius, &farRes_points, &farRes_dists);
            rescpy(&res_dists, &res_points, &farRes_dists, &farRes_points);
        }
        *points = res_points;
        *dists = res_dists;
    }
}

int pointsInSphere(KBSTnode* node, int dimension, double* center, double radius, pointData** points, double** dists){
    if(node == NULL || center == NULL || radius < 0 || dimension < 1 || points == NULL || dists == NULL) return 0;
    pointsVec res_points;
    doubleVec res_dists;
    pointsInSphere_Rec(node, dimension, center, radius, &res_points, &res_dists);
    *points = res_points.arr;
    *dists = res_dists.arr;
    return res_points.n;
}