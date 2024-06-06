#include <stdlib.h>
#include <float.h>
#include "nNearestNeighbor.h"
#include "minor_functions/priorityQ.h"
#include "KBSTnode.h"
#include "pointData.h"
#include "minor_functions/distance.h"

static priQ nNearestNeighbor_Rec(KBSTnode* head, double* target, int dimension, priQ res){
    if(head == NULL) return res;
    else{
        double dist = distance(head->point.coords, target, dimension);
        insertPriQ(&res, dist, &head->point, dimension);

        int cmp_coord = head->level % dimension;
        KBSTnode* closeBranch = head->right;
        KBSTnode* farBranch = head->left;
        if(target[cmp_coord] < head->point.coords[cmp_coord]){
            closeBranch = head->left;
            farBranch = head->right;
        }
        
        res = nNearestNeighbor_Rec(closeBranch, target, dimension, res);
        double nnnDist = peekPriQ(&res, NULL);
        if(splitDistance(head, target, dimension) < nnnDist)
            res = nNearestNeighbor_Rec(farBranch, target, dimension, res);
        return res;
    }
}

int nNearestNeighbor(KBSTnode* head, double* target, int dimension, int n, pointData** points, double** dists){
    if(head == NULL || target == NULL || dimension < 1 || n < 1) return 0;

    priQ res;
    initPriQ(&res, n);
    insertPriQ(&res, DBL_MAX, NULL, dimension);
    res = nNearestNeighbor_Rec(head, target, dimension, res);

    double nnnDist = peekPriQ(&res, NULL);
    if(nnnDist == DBL_MAX) topPriQ(&res, NULL);
    if(points != NULL) *points = res.points;
    if(dists != NULL) *dists = res.dists;
    return res.n;
}