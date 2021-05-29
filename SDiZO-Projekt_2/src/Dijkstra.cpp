#include <iostream>
#include <climits>
#include "Dijkstra.h"

Dijkstra::Dijkstra(int vertices) {
    dijkstraVertices = new DijkstraVertex *[vertices];
    position = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        dijkstraVertices[i] = new DijkstraVertex(i, INT_MAX / 2);
        position[i] = i;
    }
    heapSize = vertices;
    originalSize = vertices;
}

Dijkstra::~Dijkstra() {
    for (int i = 0; i < originalSize; ++i) {
        delete dijkstraVertices[i];
    }
    delete[] dijkstraVertices;
    delete[] position;
}

DijkstraVertex::DijkstraVertex(int vertexNumber, int distance) {
    this->vertexNumber = vertexNumber;
    this->distance = distance;
}

void DijkstraVertex::setDistance(int givenDistance) {
    DijkstraVertex::distance = givenDistance;
}

int DijkstraVertex::getDistance() const {
    return distance;
}

int DijkstraVertex::getVertexNumber() const {
    return vertexNumber;
}

void Dijkstra::createMinHeap() {
    for (int i = (heapSize - 2) / 2; i >= 0; --i)
        minHeapifyDown(i);
}

void Dijkstra::minHeapifyDown(int parentIndex) {
    int smallestIndex = parentIndex;
    int leftIndex = 2 * parentIndex + 1;
    int rightIndex = 2 * parentIndex + 2;
    if ((leftIndex < heapSize) &&
        dijkstraVertices[leftIndex]->getDistance() < dijkstraVertices[smallestIndex]->getDistance())
        smallestIndex = leftIndex;
    if ((rightIndex < heapSize) &&
        dijkstraVertices[rightIndex]->getDistance() < dijkstraVertices[smallestIndex]->getDistance())
        smallestIndex = rightIndex;
    if (smallestIndex != parentIndex) {

        position[dijkstraVertices[smallestIndex]->getVertexNumber()] = parentIndex;
        position[dijkstraVertices[parentIndex]->getVertexNumber()] = smallestIndex;
        auto swap = dijkstraVertices[parentIndex];
        dijkstraVertices[parentIndex] = dijkstraVertices[smallestIndex];
        dijkstraVertices[smallestIndex] = swap;
        minHeapifyDown(smallestIndex);
    }
}

DijkstraVertex *Dijkstra::extractMin() {
    if (heapSize > 0) {
        --heapSize;
        DijkstraVertex *mini = dijkstraVertices[0];
        position[dijkstraVertices[0]->getVertexNumber()] = heapSize;
        position[dijkstraVertices[heapSize]->getVertexNumber()] = 0;
        auto swap = dijkstraVertices[0];
        dijkstraVertices[0] = dijkstraVertices[heapSize];
        dijkstraVertices[heapSize] = swap;
        return mini;
    }
    return nullptr;
}

void
Dijkstra::dijkstraMatrix(int *&distance, int *&parent, int startingVertex, int vertices, Matrix *graphMatrix) {
    auto *heap = new Dijkstra(vertices);
    heap->dijkstraVertices[startingVertex]->setDistance(0);
    distance[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->heapSize > 0) {
        heap->createMinHeap();
        DijkstraVertex *vertexU = heap->extractMin();
        int vertexNumber = vertexU->getVertexNumber();
        for (int i = 0; i < vertices; ++i) {
            if (graphMatrix->get(i, vertexNumber) != 0) {
                int edgeWeight = graphMatrix->get(i, vertexNumber);
                for (int j = 0; j < vertices; ++j) {
                    if (graphMatrix->get(i, j) != 0) {

                        int neighbourPosition = heap->position[j];
                        int distanceU = vertexU->getDistance();
                        int distanceV = heap->dijkstraVertices[neighbourPosition]->getDistance();
                        if (distanceV > distanceU + edgeWeight) {
                            heap->dijkstraVertices[neighbourPosition]->setDistance(distanceU + edgeWeight);
                            distance[j] = distanceU + edgeWeight;
                            parent[j] = vertexU->getVertexNumber();
                        }
                        break;
                    }
                }
            }
        }
    }
    delete heap;
}

void Dijkstra::dijkstraList(int *&distance, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList) {
    auto *heap = new Dijkstra(vertices);
    heap->dijkstraVertices[startingVertex]->setDistance(0);
    distance[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->heapSize > 0) {

        heap->createMinHeap();
        DijkstraVertex *vertexU = heap->extractMin();

        auto neighbourTraverse = graphList->getHead(vertexU->getVertexNumber());
        while (neighbourTraverse != nullptr) {
            int neighbour = neighbourTraverse->neighbour;
            int edgeWeight = neighbourTraverse->edgeWeight;
            int neighbourPosition = heap->position[neighbour];
            int distanceU = vertexU->getDistance();
            int distanceV = heap->dijkstraVertices[neighbourPosition]->getDistance();
            if (distanceV > distanceU + edgeWeight) {
                heap->dijkstraVertices[neighbourPosition]->setDistance(distanceU + edgeWeight);
                distance[neighbour] = distanceU + edgeWeight;
                parent[neighbour] = vertexU->getVertexNumber();
            }
            neighbourTraverse = neighbourTraverse->next;
        }
    }
    delete heap;
}

void Dijkstra::display(int *&distance, int *&parent, int vertices, const std::string &info) {
    std::cout << info << "\n\nWierzcholek: distance | parent\n\n";
    for (int i = 0; i < vertices; ++i) {
        std::cout << i << ": " << distance[i] << " | " << parent[i] << "\n";
    }
}