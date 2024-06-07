#include <stdlib.h>
#include "insertKBST.h"
#include "KBSTnode.h"
#include "pointData.h"
#include "minor_functions/makeKBSTnode.h"

KBSTnode* insertKBST (KBSTnode* node, pointData* new_point, int dimension){
    if(new_point == NULL || dimension < 1) return NULL;
    if(node == NULL) return makeKBSTnode(new_point, dimension, 0);

    KBSTnode** placeForPoint;
    int cmp_coord = node->level % dimension;
    if(new_point->coords[cmp_coord] < node->point.coords[cmp_coord])
        placeForPoint = &node->left;
    else if(new_point->coords[cmp_coord] > node->point.coords[cmp_coord]) 
        placeForPoint = &node->right;
    else placeForPoint = node->level % 2 == 0 ? &node->left : &node->right;
        
    if(*placeForPoint == NULL){
        *placeForPoint = makeKBSTnode(new_point, dimension, node->level + 1);
        return *placeForPoint;
    }
    else insertKBST(*placeForPoint, new_point, dimension);
}