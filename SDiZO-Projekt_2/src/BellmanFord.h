#pragma once

#include <string>
#include "Matrix.h"
#include "List.h"

// help class for storing edges
class Edge {
    int vertex1;// start vertex
    int vertex2;// end vertex
    int edgeWeight;// edge value
public:

    [[nodiscard]] int getVertex1() const;

    [[nodiscard]] int getVertex2() const;

    [[nodiscard]] int getEdgeWeight() const;

    // create edge
    Edge(int vertex1, int vertex2, int edgeWeight);
};

class BellmanFord {
public:
    // implementation for matrix
    static bool
    bfMatrix(int *&distance, int *&parent, int startingVertex, int vertices, int edges, Matrix *graphMatrix);

    // implementation for list
    static bool bfList(int *&distance, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList);

    // display results
    static void display(int *&distance, int *&parent, int vertices, bool cycle, const std::string &info);
};
