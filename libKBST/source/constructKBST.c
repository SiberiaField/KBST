#include <stdlib.h>
#include "constructKBST.h"
#include "KBSTnode.h"
#include "pointData.h"
#include "minor_functions/makeKBSTnode.h"

static void swap(pointData* A, pointData* B){
    pointData sup = *A;
    *A = *B;
    *B = sup;
}

static int pivot(pointData* points, int num_of_points, int cmp_coord){
    int mediana_idx = num_of_points / 2;
    int low_idx = 0;
    int high_idx = num_of_points - 1;

    if(points[mediana_idx].coords[cmp_coord] < points[low_idx].coords[cmp_coord])
        swap(&points[low_idx], &points[mediana_idx]);
    if(points[high_idx].coords[cmp_coord] < points[low_idx].coords[cmp_coord])
        swap(&points[low_idx], &points[high_idx]);
    if(points[high_idx].coords[cmp_coord] < points[mediana_idx].coords[cmp_coord])
        swap(&points[high_idx], &points[mediana_idx]);
    return mediana_idx;
}

static int partition (pointData* points, int num_of_points, int dimension, int level){
    int cmp_coord = level % dimension;
    int mediana_idx = pivot(points, num_of_points, cmp_coord);
    double mediana = points[mediana_idx].coords[cmp_coord];
    int curr_low = 0, curr_high = num_of_points - 1;
    while(1){
        while(points[curr_low].coords[cmp_coord] < mediana)
            curr_low++;
        while(points[curr_high].coords[cmp_coord] > mediana)
            curr_high--;
        
        if(curr_low >= curr_high)
            return curr_high;

        swap(&points[curr_high], &points[curr_low]);
        curr_high--; curr_low++;
    }
}

KBSTnode* constructKBST (pointData* points, int num_of_points, int dimension, int level){
    if(points == NULL || num_of_points < 1 || dimension < 1 || level < 0) return NULL;
    if(num_of_points == 1) return makeKBSTnode(points, dimension, level);
    else{
        int middle_idx = partition(points, num_of_points, dimension, level);
        KBSTnode* left_subtree = constructKBST(points, middle_idx, dimension, level + 1);
        KBSTnode* right_subtree;
        if(middle_idx + 1 < num_of_points) 
            right_subtree = constructKBST(&points[middle_idx + 1], num_of_points - (middle_idx + 1), dimension, level + 1);
        else right_subtree = NULL;
        KBSTnode* head = makeKBSTnode(&points[middle_idx], dimension, level);
        head->left = left_subtree;
        head->right = right_subtree;
        return head;
    }        
}