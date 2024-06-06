#pragma once
#include "pointData.h"
typedef struct KBSTnode {
    pointData point;
    int level; 
    struct KBSTnode* left; 
    struct KBSTnode* right; 
} KBSTnode; 