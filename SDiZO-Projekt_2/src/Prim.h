#pragma once

#include "Matrix.h"
#include "List.h"

// help class for storing vertices
class PrimVertex {
public:
    int vertexNumber;
    int key;

    [[nodiscard]] int getVertexNumber() const;

    [[nodiscard]] int getKey() const;

    void setKey(int k);

    PrimVertex(int vertexNumber, int key);
};

// main class with help heap implementation
class Prim {

    int heapSize;
    int originalSize;

    PrimVertex **primVertices; // list of vertices
    int *position; // position[i] show where is vertex 'i'

public:
    // constructor
    explicit Prim(int vertices);

    // destructor
    virtual ~Prim();

    // Prim implementation for matrix
    static void primMatrix(int *&key, int *&parent, int startingVertex, int vertices, Matrix *graphMatrix);

    // Prim implementation for list
    static void primList(int *&key, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList);

    void createHeap();

    void heapifyDown(int parentIndex);

    // get minimal value
    PrimVertex *extractMin();

    bool isElementInHeap(int vertex);

    static void display(int *&key, int *&parent, int vertices, const std::string &info);
};