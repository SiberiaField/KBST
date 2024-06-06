#include <float.h>
#include <stdlib.h>
#include "removeKBST.h"
#include "KBSTnode.h"
#include "minor_functions/makeKBSTnode.h"

static int eqPoints(double* coords1, double* coords2, int dimension){
    for(int i = 0; i < dimension; i++)
        if(coords1[i] != coords2[i]) return 0;
    return 1;
}

static void freeNode(KBSTnode* node){
    free(node->point.coords);
    free(node->point.name);
}

static KBSTnode* minNode(KBSTnode* A, KBSTnode* B, KBSTnode* C, int cmp_coord){
    double coordA = A == NULL ? DBL_MAX : A->point.coords[cmp_coord];
    double coordB = B == NULL ? DBL_MAX : B->point.coords[cmp_coord];
    double coordC = C == NULL ? DBL_MAX : C->point.coords[cmp_coord];

    double minCoord = coordA;
    KBSTnode* min = A;
    if(coordC < minCoord){
        min = C;
        minCoord = coordC;
    }
    if(coordB < minCoord)
        min = B;
    return min;
}

static KBSTnode* findMin(KBSTnode* node, int search_coord, int dimension){
    if(node == NULL || search_coord < 0) return NULL;
    else if (node->level % dimension == search_coord){
        if(node->left == NULL) return node;
        else return findMin(node->left, search_coord, dimension);
    }
    else{
        KBSTnode* leftMin = findMin(node->left, search_coord, dimension);
        KBSTnode* rightMin = findMin(node->right, search_coord, dimension);
        return minNode(node, leftMin, rightMin, search_coord);
    }
}

KBSTnode* removeKBSTnode(KBSTnode* node, double* target, int dimension){
    if(node == NULL || target == NULL || dimension <= 0) return NULL;
    int cmp_coord = node->level % dimension;
    if(target[cmp_coord] < node->point.coords[cmp_coord]){
        node->left = removeKBSTnode(node->left, target, dimension);
        return node;
    }
    else if(target[cmp_coord] > node->point.coords[cmp_coord]){
        node->right = removeKBSTnode(node->right, target, dimension);
        return node;
    }
    else if(eqPoints(node->point.coords, target, dimension)){
        if(node->right != NULL){
            KBSTnode* min_node = findMin(node->right, cmp_coord, dimension);
            KBSTnode* new_node = makeKBSTnode(&min_node->point, dimension, node->level);
            KBSTnode* new_right = removeKBSTnode(node->right, min_node->point.coords, dimension);
            new_node->left = node->left;
            new_node->right = new_right;
            freeNode(node);
            return new_node;
        }
        else if(node->left != NULL){
            KBSTnode* min_node = findMin(node->left, cmp_coord, dimension);
            KBSTnode* new_node = makeKBSTnode(&min_node->point, dimension, node->level);
            KBSTnode* new_right = removeKBSTnode(node->left, min_node->point.coords, dimension);
            new_node->left = NULL;
            new_node->right = new_right;
            freeNode(node);
            return new_node;
        }
        else{
            freeNode(node);
            return NULL;
        }
    }
}

void removeKBST(KBSTnode* node){
    if(node == NULL) return;
    removeKBST(node->left);
    removeKBST(node->right);
    freeNode(node);
}