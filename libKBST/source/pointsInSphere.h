#pragma once
#include "KBSTnode.h"
#include "pointData.h"
int pointsInSphere(KBSTnode* node, int dimension, double* center, double radius, pointData** points, double** dists);