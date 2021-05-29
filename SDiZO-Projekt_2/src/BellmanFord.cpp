#include <iostream>
#include <climits>
#include "BellmanFord.h"

using std::cout;

Edge::Edge(int v1, int v2, int weight) {
    vertex1 = v1;
    vertex2 = v2;
    edgeWeight = weight;
}

int Edge::getVertex1() const {
    return vertex1;
}

int Edge::getVertex2() const {
    return vertex2;
}

int Edge::getEdgeWeight() const {
    return edgeWeight;
}

void Edge::setVertex1(int vertex) {
    Edge::vertex1 = vertex;
}

void Edge::setVertex2(int vertex) {
    Edge::vertex2 = vertex;
}

void Edge::setEdgeWeight(int weight) {
    Edge::edgeWeight = weight;
}

bool
BellmanFord::bfMatrix(int *&distance, int *&parent, int startingVertex, int vertices, int edges, Matrix *graphMatrix) {
    for (int i = 0; i < vertices; ++i) {
        distance[i] = INT_MAX / 2;
        parent[i] = -1;
    }
    parent[startingVertex] = -1;
    distance[startingVertex] = 0;
    Edge **graphEdges = new Edge *[edges];
    int graphEdgeIndex = 0;
//    int graphEdgeCount = 0;
    for (int i = 0; i < vertices; ++i) {
//        int vertex1 = 0;
//        int vertex2 = 0;
        for (int j = 0; j < vertices; ++j) {
            if (i != j && graphMatrix->get(i, j) != 0) {
//                vertex1 = i;
//                vertex2 = j;
                graphEdges[graphEdgeIndex] = new Edge(i,j, graphMatrix->get(i,j));
                ++graphEdgeIndex;
            }
        }
//        for (int j = 0; j < vertices; ++j) {
//            if (graphMatrix->get(i, j) == -1) {
//                vertex2 = j;
//                break;
//            }
//        }

    }
//    graphEdgeCount = graphEdgeIndex;
    bool relaxed = true;
    for (int ii = 1; ii < graphEdgeIndex && relaxed; ++ii) {
        relaxed = false;
        for (int j = 0; j < graphEdgeIndex; ++j) {
            Edge *edge = graphEdges[j];
            int u = edge->getVertex1();
            int v = edge->getVertex2();
            int weight = edge->getEdgeWeight();
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                relaxed = true;
            }
        }
    }
    if (relaxed) {
        for (int j = 0; j < graphEdgeIndex; ++j) {
            Edge *edge = graphEdges[j];
            int u = edge->getVertex1();
            int v = edge->getVertex2();
            int weight = edge->getEdgeWeight();
            if (distance[v] > distance[u] + weight) {
                delete[] distance;
                delete[] parent;
                return false;
            }
        }
    }
    for (int j = 0; j < graphEdgeIndex; ++j) {
        delete graphEdges[j];
    }
    delete[] graphEdges;
    return true;
}

bool BellmanFord::bfList(int *&distance, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList) {
    Edge **graphEdges = new Edge *[graphList->getEdges()];
    int graphEdgeIndex = 0;
    for (int j = 0; j < vertices; ++j) {
        distance[j] = INT_MAX / 2;
        parent[j] = -1;
        auto listTraverse = graphList->getHead(j);
        while (listTraverse != nullptr) {
            graphEdges[graphEdgeIndex] = new Edge(j, listTraverse->neighbour, listTraverse->edgeWeight);
            ++graphEdgeIndex;
            listTraverse = listTraverse->next;
        }
    }
    parent[startingVertex] = -1;
    distance[startingVertex] = 0;
    bool relaxed = true;
    for (int ii = 1; ii < graphEdgeIndex && relaxed; ++ii) {
        relaxed = false;
        for (int j = 0; j < graphEdgeIndex; ++j) {
            Edge *edge = graphEdges[j];
            int u = edge->getVertex1();
            int v = edge->getVertex2();
            int weight = edge->getEdgeWeight();
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                relaxed = true;
            }
        }
    }
    if (relaxed) {
        for (int j = 0; j < graphEdgeIndex; ++j) {
            Edge *edge = graphEdges[j];
            int u = edge->getVertex1();
            int v = edge->getVertex2();
            int weight = edge->getEdgeWeight();
            if (distance[v] > distance[u] + weight) {
                delete[] distance;
                delete[] parent;
                return false;
            }
        }
    }
    for (int j = 0; j < graphEdgeIndex; ++j) {
        delete graphEdges[j];
    }
    delete[] graphEdges;
    return true;
}

void BellmanFord::display(int *&distance, int *&parent, int vertices, bool cycle, const std::string &info) {
    if (!cycle) {
        cout << "\nWykryto cykl o lacznej ujemnej wadze\n\n";
    } else {
        cout << info << "\n\nWierzcholek: distance | parent\n\n";
        for (int i = 0; i < vertices; ++i) {
            cout << i << ": " << distance[i] << " | " << parent[i] << "\n";
        }
    }
}
