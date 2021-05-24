#pragma once

#include <string>
#include "Matrix.h"
#include "List.h"

class DijkstraVertex {
    int vertexNumber;
    int distance;
public:
    [[nodiscard]] int getVertexNumber() const;

    [[nodiscard]] int getDistance() const;

    void setDistance(int givenDistance);

    DijkstraVertex(int vertexNumber, int distance);
};

class Dijkstra {
    int heapSize;
    int originalSize;

public:
    explicit Dijkstra(int vertices);

    virtual ~Dijkstra();

    DijkstraVertex **dijkstraVertices;
    int *position;

    static void
    dijkstraMatrix(int *&distance, int *&parent, int startingVertex, int vertices, Matrix *graphMatrix);

    static void dijkstraList(int *&distance, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList);

    static void display(int *&distance, int *&parent, int vertices, const std::string &info);

    void createMinHeap();

    void minHeapifyDown(int parentIndex);

    DijkstraVertex *extractMin();
};