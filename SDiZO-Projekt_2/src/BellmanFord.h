#pragma once

#include <string>
#include "Matrix.h"
#include "List.h"

class BellmanFord {
public:
    static void bfMatrix(int *&distance, int *&parent, int startingVertex, int vertices, int edges, Matrix *graphMatrix);

    static void bfList(int *&distance, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList);

    static void display(int *&distance, int *&parent, int vertices, const std::string &info);
};
