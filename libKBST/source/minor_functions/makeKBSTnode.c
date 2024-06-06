#include <stdlib.h>
#include <string.h>
#include "makeKBSTnode.h"
#include "../KBSTnode.h"
#include "../pointData.h"

KBSTnode* makeKBSTnode(pointData* point, int dimension, int level){
    if(point == NULL || dimension < 1 || level < 0) return NULL;

    KBSTnode* newNode = (KBSTnode*)malloc(sizeof(KBSTnode));
    newNode->level = level;
    newNode->point.coords = (double*)malloc(sizeof(double) * dimension);
    memcpy(newNode->point.coords, point->coords, sizeof(double) * dimension);
    newNode->left = newNode->right = NULL;

    if(point->name == NULL || point->nameLen < 1){
        newNode->point.name = NULL;
        newNode->point.nameLen = 0;
    }
    else{
        newNode->point.nameLen = point->nameLen;
        newNode->point.name = (char*)malloc(sizeof(char) * point->nameLen);
        memcpy(newNode->point.name, point->name, sizeof(char) * point->nameLen);
    }
    return newNode;
}