#pragma once

#include "List.h"
#include "Matrix.h"

class KruskalEdge {
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
    // constructor
    KruskalEdge(int vertex1, int vertex2, int edgeWeight);
};

class Kruskal {
public:
    // Kruskal implementation for matrix
    static void kruskalMatrix(KruskalEdge **mstEdges, int vertices, int edges, Matrix *graphMatrix);
    // Kruskal implementation for list
    static void kruskalList(KruskalEdge **mstEdges, int vertices, int edges, AdjacencyList *graphList);

    static int kruskalFindSet(int *parent, int x);
    // display kruskal results
    static void display(KruskalEdge **mstEdges, int vertices, const std::string &info);
};
