#include <iostream>
#include "Kruskal.h"

using std::cout;

KruskalEdge::KruskalEdge(int v1, int v2, int weight) {
    vertex1 = v1;
    vertex2 = v2;
    edgeWeight = weight;
}

int KruskalEdge::getVertex1() const {
    return vertex1;
}

int KruskalEdge::getVertex2() const {
    return vertex2;
}

int KruskalEdge::getEdgeWeight() const {
    return edgeWeight;
}

void KruskalEdge::setVertex1(int vertex) {
    KruskalEdge::vertex1 = vertex;
}

void KruskalEdge::setVertex2(int vertex) {
    KruskalEdge::vertex2 = vertex;
}

void KruskalEdge::setEdgeWeight(int weight) {
    KruskalEdge::edgeWeight = weight;
}

int Kruskal::kruskalFindSet(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = kruskalFindSet(parent, parent[x]);
    return parent[x];
}

void Kruskal::kruskalList(KruskalEdge **mstEdges, int vertices, int edges, AdjacencyList *graphList) {
    int *parent = new int[vertices];
    int *rank = new int[vertices];
    auto **graphEdges = new KruskalEdge *[2 * edges]; // 2 * edges because of duplicates
    int graphEdgeIndex = 0;
    int graphEdgesCount;
    for (int j = 0; j < vertices; ++j) {
        parent[j] = j;
        rank[j] = 0;
        auto listTraverse = graphList->getHead(j);
        while (listTraverse != nullptr) {
            graphEdges[graphEdgeIndex] = new KruskalEdge(j, listTraverse->neighbour, listTraverse->edgeWeight);
            KruskalEdge *swap = graphEdges[graphEdgeIndex];
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
    graphEdgesCount = graphEdgeIndex;
    int mstEdgeIndex = 0;
    for (graphEdgeIndex = 0; graphEdgeIndex < graphEdgesCount; ++graphEdgeIndex) {
        KruskalEdge *edge = graphEdges[graphEdgeIndex];
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

void Kruskal::kruskalMatrix(KruskalEdge **mstEdges, int vertices, int edges, Matrix *graphMatrix) {
    int *parent = new int[vertices];
    int *rank = new int[vertices];
    auto **graphEdges = new KruskalEdge *[edges];
    int graphEdgesCount = 0;
    int graphEdgeIndex = 0;
    int mstEdgeIndex = 0;
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < vertices; ++i) {
        int j = i + 1;
        for (; j < vertices; ++j) {
            if (i != j && graphMatrix->get(i, j) != 0) {
                graphEdges[graphEdgeIndex] = new KruskalEdge(i, j, graphMatrix->get(i, j));
                KruskalEdge *swap = graphEdges[graphEdgeIndex];
                int k = graphEdgeIndex - 1;
                while (k >= 0 && graphEdges[k]->getEdgeWeight() > swap->getEdgeWeight()) {
                    graphEdges[k + 1] = graphEdges[k];
                    --k;
                }
                graphEdges[k + 1] = swap;
                ++graphEdgeIndex;
            }
        }
        graphEdgesCount = graphEdgeIndex;
    }
    for (graphEdgeIndex = 0; graphEdgeIndex < graphEdgesCount; ++graphEdgeIndex) {
        KruskalEdge *edge = graphEdges[graphEdgeIndex];
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

// Display generated results
void Kruskal::display(KruskalEdge **mstEdges, int vertices, const std::string &info) {
    cout << info << " \n\nKrawedzie MST:\n\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << mstEdges[i]->getVertex1() << " - " << mstEdges[i]->getVertex2() << " : Waga = "
             << mstEdges[i]->getEdgeWeight()
             << "\n";
    }
}