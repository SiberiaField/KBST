#include <stdlib.h>
#include <string.h>
#include "priorityQ.h"
#include "../KBSTnode.h"
#include "../pointData.h"

void initPriQ(priQ* Q, int cap){
    Q->n = 0;
    Q->cap = cap;
    Q->dists = (double*)malloc(sizeof(double) * cap);
    Q->points = (pointData*)malloc(sizeof(pointData) * cap);
}
    
static void siftUp(priQ* Q, int idx){
    double curr_node_dist = Q->dists[idx];
    pointData curr_node_point = Q->points[idx];
    while(idx > 0){
        int parentIdx = (idx - 1) / 2;
        if(curr_node_dist > Q->dists[parentIdx]){
            Q->dists[idx] = Q->dists[parentIdx];
            Q->points[idx] = Q->points[parentIdx];
            idx = parentIdx;
        }
        else break;
    }
    Q->dists[idx] = curr_node_dist;
    Q->points[idx] = curr_node_point;
}

static int highestPriChild(priQ* Q, int parent_idx){
    int left_child_idx = parent_idx * 2 + 1;
    int right_child_idx = (parent_idx + 1) * 2;
    if(right_child_idx >= Q->n){
        return left_child_idx;
    }
    if(Q->dists[left_child_idx] > Q->dists[right_child_idx]){
        return right_child_idx;
    }
    else return left_child_idx;
}

static int firstLeafIdx(int priQ_size){
    return (priQ_size - 2) / 2 + 1;
}

static void siftDown(priQ* Q, int idx){
    double curr_node_dist = Q->dists[idx];
    pointData curr_node_point = Q->points[idx];
    while(idx < firstLeafIdx(Q->n)){
        int highestChild_idx = highestPriChild(Q, idx);
        if(Q->dists[highestChild_idx] > curr_node_dist){
            Q->dists[idx] = Q->dists[highestChild_idx];
            Q->points[idx] = Q->points[highestChild_idx];
            idx = highestChild_idx;
        }
        else break;
    }
    Q->dists[idx] = curr_node_dist;
    Q->points[idx] = curr_node_point;
}

double topPriQ(priQ* Q, pointData* point){
    if(Q->n <= 0) return -1; 
    int last_idx = Q->n - 1;
    double last_node_dist = Q->dists[last_idx];
    pointData last_node_point = Q->points[last_idx];
    Q->n--;
    if(Q->n == 0) {
        if(point != NULL ) *point = last_node_point;
        return last_node_dist;
    }
    else{
        double first_node_dist = Q->dists[0];
        pointData first_node_point = Q->points[0];
        Q->dists[0] = last_node_dist;
        Q->points[0] = last_node_point;
        siftDown(Q, 0);
        if(point != NULL) *point = first_node_point;
        return first_node_dist;
    }
}

double peekPriQ(priQ* Q, pointData* point){
    if(Q->n <= 0) {
        return -1;
    }
    if(point != NULL) *point = Q->points[0];
    return Q->dists[0];
}

int insertPriQ(priQ* Q, double dist, pointData* point){
    if(Q == NULL || Q->dists == NULL || Q->points == NULL) return 1;
    if((Q->n == Q->cap) && (peekPriQ(Q, NULL) > dist)) topPriQ(Q, NULL);
    if(Q->n < Q->cap){
        Q->dists[Q->n] = dist;
        if(point != NULL) Q->points[Q->n] = *point;
        else {
            Q->points[Q->n].name = NULL;
            Q->points[Q->n].coords = NULL;
            Q->points[Q->n].nameLen = 0;
        }
        Q->n++;
        siftUp(Q, Q->n - 1);
    }
    return 0;
}