#pragma once

#include "Matrix.h"
#include "List.h"

class PrimVertex {
public:
    int vertexNumber;
    int key;

    int getVertexNumber() const;

    void setVertexNumber(int vertexValue);

    int getKey() const;

    void setKey(int k);

    PrimVertex(int vertexNumber, int key);
};

class Prim {

    int heapSize;
    int originalSize;

    PrimVertex **primVertices; // list of vertices
    int *position; // position[i] show where is vertex 'i'

public:
    explicit Prim(int vertices);

    virtual ~Prim();

    static void primMatrix(int *&key, int *&parent, int startingVertex, int vertices, Matrix *graphMatrix);

    static void primList(int *&key, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList);

    void createMinHeap();

    void minHeapifyDown(int parentIndex);

    PrimVertex *extractMin();

    bool isElementInHeap(int vertex);

    static void display(int *&key, int *&parent, int vertices, const std::string &info);
};