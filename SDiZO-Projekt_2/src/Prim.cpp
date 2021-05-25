#include <iostream>
#include <climits>
#include "Prim.h"

using std::cout;

PrimVertex::PrimVertex(int vertexNumber, int key) : vertexNumber(vertexNumber), key(key) {}

int PrimVertex::getVertexNumber() const {
    return vertexNumber;
}

void PrimVertex::setVertexNumber(int vertexValue) {
    PrimVertex::vertexNumber = vertexValue;
}

int PrimVertex::getKey() const {
    return key;
}

void PrimVertex::setKey(int k) {
    PrimVertex::key = k;
}

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

Prim::~Prim() {
    for (int i = 0; i < originalSize; ++i) {
        delete primVertices[i];
    }
    delete[] primVertices;
    delete[] position;
}

bool Prim::isElementInHeap(int vertex) {
    return position[vertex] < heapSize;
}

void Prim::createMinHeap() {
    for (int i = (heapSize - 2) / 2; i >= 0; --i)
        minHeapifyDown(i);
}

void Prim::minHeapifyDown(int parentIndex) {
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
        minHeapifyDown(smallestIndex);
    }
}

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

void Prim::primMatrix(int *&key, int *&parent, int startingVertex, int vertices, Matrix *graphMatrix) {
    //stos wierzchołków Prima (tzn. obiektów wierzchołek posiadających swój numer, oraz key)
    auto *heap = new Prim(vertices);
    heap->primVertices[startingVertex]->setKey(0);
    key[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->heapSize > 0) {
        //tworzymy stos (aby mieć wierzchołek o najmniejszej wadze), trzeba co pętlę ponieważ w pętli zmieniają się elementy stosu
        heap->createMinHeap();
        PrimVertex *vertexU = heap->extractMin();
        int vertexNumber = vertexU->getVertexNumber();
        for (int i = 0; i < vertices; ++i) {
            if (graphMatrix->get(vertexNumber,i) != 0) {
                int edgeWeight = graphMatrix->get(vertexNumber,i);
//                for (int j = 0; j < vertices; ++j) {
//                    if (graphMatrix->get(i, j) != 0 && j != vertexNumber) {
                        // 'j' to sąsiad (neighbour)
                        if (heap->isElementInHeap(i)) {
                            int neighbourPosition = heap->position[i];
                            if (edgeWeight < heap->primVertices[neighbourPosition]->getKey()) {
                                heap->primVertices[neighbourPosition]->setKey(edgeWeight);
                                key[i] = edgeWeight;
                                parent[i] = vertexU->getVertexNumber();
                            }
//                            break;
                        }
                    }
                }
//            }
//        }
    }
    delete heap;
}

void Prim::primList(int *&key, int *&parent, int startingVertex, int vertices, AdjacencyList *graphList) {
    // Prim heap
    auto *heap = new Prim(vertices);
    heap->primVertices[startingVertex]->key = 0;
    key[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->heapSize > 0) {
        // create heap
        heap->createMinHeap();
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

void Prim::display(int *&key, int *&parent, int vertices, const std::string &info) {
    cout << "\n" << info << "\twierzcholek: klucz/rodzic\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": " << key[i] << "/" << parent[i] << "\n";
    }
    cout << "\nKrawedzie MST:\n";
    for (int i = 0; i < vertices; ++i) {
        if (parent[i] != -1) {
            cout << i << " - " << parent[i] << " : Waga = " << key[i] << "\n";
        }
    }
}


