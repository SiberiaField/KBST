#include <stdlib.h>
#include "insertKBST.h"
#include "KBSTnode.h"
#include "pointData.h"
#include "minor_functions/makeKBSTnode.h"

KBSTnode* insertKBST (KBSTnode* head, pointData* new_point,  int dimension){
    if(new_point == NULL || dimension < 0) return NULL;
    if(head == NULL) return makeKBSTnode(new_point, dimension, 0);

    KBSTnode** placeForPoint;
    int cmp_coord = head->level % dimension;
    if(new_point->coords[cmp_coord] < head->point.coords[cmp_coord])
        placeForPoint = &head->left;
    else if(new_point->coords[cmp_coord] > head->point.coords[cmp_coord]) 
        placeForPoint = &head->right;
    else placeForPoint = head->level % 2 == 0 ? &head->left : &head->right;
        
    if(*placeForPoint == NULL){
        *placeForPoint = makeKBSTnode(new_point, dimension, head->level + 1);
        return *placeForPoint;
    }
    else insertKBST(*placeForPoint, new_point, dimension);
}