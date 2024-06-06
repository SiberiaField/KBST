#pragma once
#include "KBSTnode.h"
#include "pointData.h"
int nNearestNeighbor(KBSTnode* head, double* target, int dimension, int n, pointData** points, double** dists);