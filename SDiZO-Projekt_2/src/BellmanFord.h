#pragma once

#include <string>
#include "Matrix.h"
#include "List.h"

class Edge {
    int vertex1;
    int vertex2;
    int edgeWeight;
public:
    void setVertex1(int vertex);

    void setVertex2(int vertex);

    void setEdgeWeight(int weight);

    [[nodiscard]] int getVertex1() const;

    [[nodiscard]] int getVertex2() const;

    [[nodiscard]] int getEdgeWeight() const;

    Edge(int vertex1, int vertex2, int edgeWeight);
};

class BellmanFord {
public:
    static bool bfMatrix(int *&distance, int *&parent, int startingVertex, int vertices, int edges, Matrix *graphMatrix);

    static bool bfList(int *&distance, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList);

    static void display(int *&distance, int *&parent, int vertices, bool cycle, const std::string &info);
};
