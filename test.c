#include "libKBST.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void print(KBSTnode* head){
    if(head == NULL) return;
    printf("%s", head->point.name);
    printf("(");
    if(head->left != NULL)
        print(head->left);
    printf(", ");
    if(head->right != NULL)
        print(head->right);
    printf(")");
}

int main(){
    srand(time(NULL));
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int num_of_points = 8, dimension = 2;
    pointData* points = (pointData*)malloc(sizeof(pointData) * num_of_points);

    for(int i = 0; i < num_of_points; i++){
        points[i].coords = (double*)malloc(sizeof(double) * dimension);
        for(int j = 0; j < dimension; j++)
            scanf("%lf ", &points[i].coords[j]);
        points[i].name = (char*)malloc(sizeof(char) * 2);
        scanf("%c ", &points[i].name[0]);
        points[i].name[1] = '\0';
        points[i].nameLen = 2;
    }

    KBSTnode* head = constructKBST(points, num_of_points, dimension, 0);
    printf("TREE:\n");
    print(head);

    int n = 7;
    pointData* neighbors;
    double* dists;
    double p[2] = {-0.5, -2.5};
    int neighbors_size = nNearestNeighbor(head, p, dimension, 2, &neighbors, &dists);
    printf("\n\nTESTS:\nNeighbors: ");
    for(int i = 0; i < neighbors_size; i++)
        printf("%s(%0.1lf, %0.1lf); ", neighbors[i].name, neighbors[i].coords[0], neighbors[i].coords[1]);

    pointData* answ_points;
    double* answ_dists;
    printf("\nIn sphere: ");
    int answ_size = pointsInSphere(head, dimension, p, 2.5, &answ_points, &answ_dists);
    for(int i = 0; i < answ_size; i++){
        printf("%s %.3lf; ", answ_points[i].name, answ_dists[i]);
    }

    printf("\nIn rectangle: ");
    double rectangle[4] = {-2, 3.5, -4, 2};
    answ_size = pointsInRectangle(head, dimension, rectangle, &answ_points);
    for(int i = 0; i < answ_size; i++){
        printf("%s ", answ_points[i].name);
    }
    printf("\n");

    printf("Remove A and H:\n");
    double H[2] = {3, -3} ;
    head = removeKBSTnode(head, H, dimension);
    assert(!searchKBST(head, H, dimension));
    double A[2] = {0, 5};
    head = removeKBSTnode(head, A, dimension);
    assert(!searchKBST(head, A, dimension));
    print(head);
    printf("\n");

    printf("Remove H again:\n");
    head = removeKBSTnode(head, H, dimension);
    print(head);
    printf("\n");

    printf("Insert A:\n");
    pointData pointA;
    pointA.coords = A;
    pointA.name = (char*)malloc(sizeof(char) * 2);
    pointA.name[0] = 'A';
    pointA.name[1] = '\0';
    pointA.nameLen = 2;
    insertKBST(head, &pointA, dimension);
    printf("Insert complete!\n");
    assert(searchKBST(head, A, dimension));
    print(head);
    printf("\nEND\n");
    removeKBST(head);
    return 0;
}