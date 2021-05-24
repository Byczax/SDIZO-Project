#include <iostream>
#include "Kruskal.h"

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

int Kruskal::kruskalFindSet(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = kruskalFindSet(parent, parent[x]);
    return parent[x];
}

void Kruskal::kruskalList(Edge **mstEdges, int vertices, int edges, AdjacencyList *graphList) {
    int *parent = new int[vertices];
    int *rank = new int[vertices];
    Edge **graphEdges = new Edge *[2 * edges]; //2*edges because of duplicates
    int graphEdgeIndex = 0;

    for (int j = 0; j < vertices; ++j) {
        parent[j] = j;
        rank[j] = 0;
        auto listTraverse = graphList->getHead(j);
        while (listTraverse != nullptr) {
            graphEdges[graphEdgeIndex] = new Edge(j, listTraverse->neighbour, listTraverse->edgeWeight);
            Edge *swap = graphEdges[graphEdgeIndex];
            int k = graphEdgeIndex - 1;
            while (k >= 0 && graphEdges[k]->getEdgeWeight() > swap->getEdgeWeight()) {
                graphEdges[k + 1] = graphEdges[k];
                --k;
            }
            graphEdges[k + 1] = swap;
            ++graphEdgeIndex;
            listTraverse = listTraverse->next;
        }
    }
    int mstEdgeIndex = 0;
    for (graphEdgeIndex = 0; graphEdgeIndex < 2 * edges; ++graphEdgeIndex) {
        Edge *edge = graphEdges[graphEdgeIndex];
        int v1 = edge->getVertex1();
        int v2 = edge->getVertex2();
        int set1 = Kruskal::kruskalFindSet(parent, v1);
        int set2 = Kruskal::kruskalFindSet(parent, v2);
        if (set1 != set2) {
            mstEdges[mstEdgeIndex]->setVertex1(v1);
            mstEdges[mstEdgeIndex]->setVertex2(v2);
            mstEdges[mstEdgeIndex]->setEdgeWeight(edge->getEdgeWeight());
            ++mstEdgeIndex;
            if (rank[set1] < rank[set2])
                parent[set1] = set2;
            else
                parent[set2] = set1;
            if (rank[set1] == rank[set2])
                ++rank[set1];
        }
        delete graphEdges[graphEdgeIndex];
    }
    delete[] parent;
    delete[] rank;
    delete[] graphEdges;
}

void Kruskal::kruskalMatrix(Edge **mstEdges, int vertices, int edges, Matrix *graphMatrix) {
    int *parent = new int[vertices];
    int *rank = new int[vertices];
    Edge **graphEdges = new Edge *[edges];
    int graphEdgeIndex = 0;
    int mstEdgeIndex = 0;
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < vertices; ++i) {
        int vertex1 = 0;
        int vertex2 = 0;
        int j = 0;
        for (; j < vertices; ++j) {
            if (graphMatrix->get(i, j) != 0) {
                vertex1 = j;
                ++j;
                break;
            }
        }
        for (; j < vertices; ++j) {
            if (graphMatrix->get(i, j) != 0) {
                vertex2 = j;
                break;
            }
        }
        graphEdges[graphEdgeIndex] = new Edge(vertex1, vertex2, graphMatrix->get(vertex1, vertex2));
        Edge *swap = graphEdges[graphEdgeIndex];
        int k = graphEdgeIndex - 1;
        while (k >= 0 && graphEdges[k]->getEdgeWeight() > swap->getEdgeWeight()) {
            graphEdges[k + 1] = graphEdges[k];
            --k;
        }
        graphEdges[k + 1] = swap;
        ++graphEdgeIndex;
    }
    for (graphEdgeIndex = 0; graphEdgeIndex < vertices; ++graphEdgeIndex) {
        Edge *edge = graphEdges[graphEdgeIndex];
        int v1 = edge->getVertex1();
        int v2 = edge->getVertex2();
        int set1 = Kruskal::kruskalFindSet(parent, v1);
        int set2 = Kruskal::kruskalFindSet(parent, v2);
        if (set1 != set2) {
            mstEdges[mstEdgeIndex]->setVertex1(v1);
            mstEdges[mstEdgeIndex]->setVertex2(v2);
            mstEdges[mstEdgeIndex]->setEdgeWeight(edge->getEdgeWeight());
            ++mstEdgeIndex;
            if (rank[set1] < rank[set2])
                parent[set1] = set2;
            else
                parent[set2] = set1;
            if (rank[set1] == rank[set2])
                ++rank[set1];
        }
        delete graphEdges[graphEdgeIndex];
    }
    delete[] parent;
    delete[] rank;
    delete[] graphEdges;
}

void Kruskal::display(Edge **mstEdges, int vertices, const std::string &info) {
    cout << info << " \nKrawedzie MST:\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << mstEdges[i]->getVertex1() << " - " << mstEdges[i]->getVertex2() << " : Waga = "
             << mstEdges[i]->getEdgeWeight()
             << "\n";
    }
}