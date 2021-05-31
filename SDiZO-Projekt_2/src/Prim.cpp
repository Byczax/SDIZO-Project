#include <iostream>
#include <climits>
#include "Prim.h"

using std::cout;

PrimVertex::PrimVertex(int vertexNumber, int key) : vertexNumber(vertexNumber), key(key) {}

int PrimVertex::getVertexNumber() const {
    return vertexNumber;
}

int PrimVertex::getKey() const {
    return key;
}

void PrimVertex::setKey(int k) {
    PrimVertex::key = k;
}

// constructor
Prim::Prim(int vertices) {
    primVertices = new PrimVertex *[vertices];
    position = new int[vertices];

    for (int i = 0; i < vertices; ++i) {
        primVertices[i] = new PrimVertex(i, INT_MAX / 2); // INT_MAX/2 as infinity
        position[i] = i;
    }
    heapSize = vertices;
    originalSize = vertices;
}

// destructor
Prim::~Prim() {
    for (int i = 0; i < originalSize; ++i) {
        delete primVertices[i];
    }
    delete[] primVertices;
    delete[] position;
}

// find if vertex is in heap
bool Prim::isElementInHeap(int vertex) {
    return position[vertex] < heapSize;
}

void Prim::createHeap() {
    for (int i = (heapSize - 2) / 2; i >= 0; --i)
        heapifyDown(i);
}

// heap function
void Prim::heapifyDown(int parentIndex) {
    int smallestIndex = parentIndex;
    int leftIndex = 2 * parentIndex + 1;
    int rightIndex = 2 * parentIndex + 2;
    if ((leftIndex < heapSize) && primVertices[leftIndex]->key < primVertices[smallestIndex]->key)
        smallestIndex = leftIndex;
    if ((rightIndex < heapSize) && primVertices[rightIndex]->key < primVertices[smallestIndex]->key)
        smallestIndex = rightIndex;
    if (smallestIndex != parentIndex) {
        position[primVertices[smallestIndex]->vertexNumber] = parentIndex;
        position[primVertices[parentIndex]->vertexNumber] = smallestIndex;
        auto swap = primVertices[parentIndex];
        primVertices[parentIndex] = primVertices[smallestIndex];
        primVertices[smallestIndex] = swap;
        heapifyDown(smallestIndex);
    }
}

// get minimal value
PrimVertex *Prim::extractMin() {
    if (heapSize > 0) {
        --heapSize;
        PrimVertex *mini = primVertices[0];
        position[primVertices[0]->vertexNumber] = heapSize;
        position[primVertices[heapSize]->vertexNumber] = 0;
        auto swap = primVertices[0];
        primVertices[0] = primVertices[heapSize];
        primVertices[heapSize] = swap;
        return mini;
    }
    return nullptr;
}

// prim implementation for matrix
void Prim::primMatrix(int *&key, int *&parent, int startingVertex, int vertices, Matrix *graphMatrix) {
    auto *heap = new Prim(vertices);
    heap->primVertices[startingVertex]->setKey(0);
    key[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->heapSize > 0) {
        heap->createHeap();
        PrimVertex *vertexU = heap->extractMin();
        int vertexNumber = vertexU->getVertexNumber();
        for (int i = 0; i < vertices; ++i) {
            if (graphMatrix->get(vertexNumber, i) != 0 && vertexNumber != i) {
                int edgeWeight = graphMatrix->get(vertexNumber, i);
                if (heap->isElementInHeap(i)) {
                    int neighbourPosition = heap->position[i];
                    if (edgeWeight < heap->primVertices[neighbourPosition]->getKey()) {
                        heap->primVertices[neighbourPosition]->setKey(edgeWeight);
                        key[i] = edgeWeight;
                        parent[i] = vertexU->getVertexNumber();
                    }
                }
            }
        }
    }
    delete heap;
}

// prim implementation for list
void Prim::primList(int *&key, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList) {
    // Prim heap
    auto *heap = new Prim(vertices);
    heap->primVertices[startingVertex]->key = 0;
    key[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->heapSize > 0) {
        // create heap
        heap->createHeap();
        PrimVertex *vertexU = heap->extractMin();

        auto neighbourTraverse = graphList->getHead(vertexU->vertexNumber);
        while (neighbourTraverse != nullptr) {
            int neighbour = neighbourTraverse->neighbour;
            if (heap->isElementInHeap(neighbour)) {
                int edgeWeight = neighbourTraverse->edgeWeight;
                int neighbourPosition = heap->position[neighbour];
                if (edgeWeight < heap->primVertices[neighbourPosition]->key) {
                    heap->primVertices[neighbourPosition]->key = edgeWeight;
                    key[neighbour] = edgeWeight;
                    parent[neighbour] = vertexU->vertexNumber;
                }
            }
            neighbourTraverse = neighbourTraverse->next;
        }
    }
    delete heap;
}

// Display generated results
void Prim::display(int *&key, int *&parent, int vertices, const std::string &info) {
    cout << "\n" << info << "\nwierzcholek: klucz | rodzic\n\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": " << key[i] << " | " << parent[i] << "\n";
    }
    cout << "\nKrawedzie MST:\n\n";
    for (int i = 0; i < vertices; ++i) {
        if (parent[i] != -1) {
            cout << i << " - " << parent[i] << " : Waga = " << key[i] << "\n";
        }
    }
}