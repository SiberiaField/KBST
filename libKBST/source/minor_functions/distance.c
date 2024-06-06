#include <math.h>
#include "distance.h"
#include "../KBSTnode.h"

static double abs_lf(double num){
    return num < 0 ? -num : num;
}

double splitDistance(KBSTnode* node, double* point, int dimension){
    int cmp_coord = node->level % dimension;
    return abs_lf(node->point.coords[cmp_coord] - point[cmp_coord]);
}

double distance(double* A, double* B, int dimension){
    double sum = 0;
    for(int i = 0; i < dimension; i++)
        sum += pow(A[i] - B[i], 2);
    return sqrt(sum);
}