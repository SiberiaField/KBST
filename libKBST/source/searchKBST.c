#include <stdlib.h>
#include "searchKBST.h"
#include "KBSTnode.h"

static int eqPoints(double* coords1, double* coords2, int dimension){
    for(int i = 0; i < dimension; i++)
        if(coords1[i] != coords2[i]) return 0;
    return 1;
}

int searchKBST (KBSTnode* node, double* target, int dimension){ 
    if(node == NULL || target == NULL || dimension < 1) return 0;

    int cmp_coord = node->level % dimension;
    if(target[cmp_coord] > node->point.coords[cmp_coord])
        return searchKBST(node->right, target, dimension);
    else if (target[cmp_coord] < node->point.coords[cmp_coord] )
        return searchKBST(node->left, target, dimension);
    else if(eqPoints(node->point.coords, target, dimension)) return 1;
    else searchKBST(node->level % 2 == 0 ? node->left : node->right, target, dimension);
} 