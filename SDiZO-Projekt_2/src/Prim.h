#pragma once

#include "Matrix.h"
#include "List.h"

class PrimVertex {

public:
    int vertexNumber;
    int key;

    PrimVertex(int vertexNumber, int key);
};

class Prim {

    int heapSize;
    int originalSize;

    PrimVertex **primVertices;
    int *position; // position[i] pokazuje gdzie w stosie jest wierzchołek 'i'
public:
    static void primMatrix(int *&key, int *&parent, int startingVertex, Matrix *graphMatrix);

    static void primList(int *&key, int *&parent, int startingVertex, AdjacencyList *graphList);


};


