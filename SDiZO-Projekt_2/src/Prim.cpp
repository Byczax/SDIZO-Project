#include "Prim.h"

PrimVertex::PrimVertex(int vertexNumber, int key) : vertexNumber(vertexNumber), key(key) {}

void Prim::primMatrix(int *&key, int *&parent, int startingVertex, Matrix *graphMatrix) {

}

void Prim::primList(int *&key, int *&parent, int startingVertex, AdjacencyList *graphList) {
    //stos wierzchołków Prima (tzn. obiektów wierzchołek posiadających swój numer, oraz key)
//    auto *heap = new PrimVertexHeap(vertices);
//    heap->primVertices[startingVertex]->setKey(0);
//    key[startingVertex] = 0;
//    parent[startingVertex] = -1;
//    while (heap->hasElements()) {
//        //tworzymy stos (aby mieć wierzchołek o najmniejszej wadze), trzeba co pętlę ponieważ w pętli zmieniają się elementy stosu
//        heap->createMinHeap();
//        PrimVertex *vertexU = heap->extractMin();
//        //neighbourTraverse - obiekt (ListElement) za pomocą którego dobieramy się do wszystkich sąsiadów wierzchołka z listy sąsiedztwa
//        auto neighbourTraverse = adjacencyLists[vertexU->getVertexNumber()]->getHead();
//        while (neighbourTraverse != nullptr) {
//            int neighbour = neighbourTraverse->neighbour;
//            if (heap->isElementInHeap(neighbour)) {
//                int edgeWeight = neighbourTraverse->edgeWeight;
//                int neighbourPosition = heap->position[neighbour];
//                if (edgeWeight < heap->primVertices[neighbourPosition]->getKey()) {
//                    heap->primVertices[neighbourPosition]->setKey(edgeWeight);
//                    key[neighbour] = edgeWeight;
//                    parent[neighbour] = vertexU->getVertexNumber();
//                }
//            }
//            neighbourTraverse = neighbourTraverse->next;
//        }
//    }
//    delete heap;
}


