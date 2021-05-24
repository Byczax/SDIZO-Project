#include <chrono>
#include <string>
#include <fstream>
#include <random>

#include "Essentials.h"

using std::string;

/**
 * Read edgeWeight from file
 * @param filename
 * @return
 */
void
Essentials::getDataFromFile(const string &filename, Matrix *&matrixGraph, AdjacencyList *&matrixList, bool directed) {
    std::ifstream is(filename);

    int edges, vertices;
    if (!(is >> edges >> vertices)) { throw; }
    int edgeStart, edgeEnd, edgeValue;
    delete matrixGraph;
    delete matrixList;
    matrixGraph = new Matrix(vertices, vertices);
    matrixList = new AdjacencyList(vertices, edges);
    if (directed) {
        for (int i = 0; i < edges; ++i) {
            if (!(is >> edgeStart >> edgeEnd >> edgeValue)) { throw; }
            matrixGraph->addUndirectedEdge(edgeStart, edgeEnd, edgeValue);
            matrixList->addUndirectedEdge(edgeStart, edgeEnd, edgeValue);
        }
    } else {
        for (int i = 0; i < edges; ++i) {
            if (!(is >> edgeStart >> edgeEnd >> edgeValue)) { throw; }
            matrixGraph->addDirectedEdge(edgeStart, edgeEnd, edgeValue);
        }
    }
}

//int Essentials::randomNumber(int minimum, int maximum) {
//    return minimum + rand() % (maximum - minimum + 1);
//}

int Essentials::randomNumber(int mini, int maxi) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(mini, maxi);
    return distribution(mt);
}

void Essentials::generateRandomGraph(int vertices, int density, Matrix *&matrixGraph, AdjacencyList *&listGraph,
                                     bool directed) {
    int possibleEdges = (vertices * (vertices - 1)); // all possible edges
    int wantedEdges = (density * possibleEdges) / 100; // all wanted edges
    auto *verticesList = new List(); // create empty list for vertices
    auto *allEdges = new List();
    // if wanted edges is smaller than needed edges for creating graph
    if (wantedEdges < vertices - 1) {
        wantedEdges = vertices - 1;
    }
    // fill list with all vertices
    for (int i = 0; i < vertices; ++i) {
        verticesList->addElement(-1, i);
    }
    delete matrixGraph;
    delete listGraph;
    matrixGraph = new Matrix(vertices, vertices);
    listGraph = new AdjacencyList(vertices, 0);

    int randomVertex1;
    int randomVertex2;
    int randomIndex1 = 0;
    int randomIndex2 = 0;
    int edgeCounter = vertices - 1;
    int randomValue;

    if (directed) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (i != j) {
                    allEdges->addElement(i, j);
                }
            }
        }
        wantedEdges -= edgeCounter;
        randomVertex1 = 0; // get first vertex = 0
        verticesList->removeElementFront();// remove 0 from list
        int firstVertex = randomVertex1; // set 0 as first vertex
        while (edgeCounter > 0) {
            randomIndex2 = randomNumber(0, verticesList->getSize() - 1); // get random vertex from list without 0

            randomVertex2 = verticesList->findValue(randomIndex2); // get that random vertex

            verticesList->removeElementAnywhere(randomIndex2); // remove chosen above vertex from list

            --edgeCounter; // decrement

//            randomIndex1 = randomIndex2; //
            randomValue = randomNumber(1, 999); // get random value for edge

            matrixGraph->addDirectedEdge(randomVertex1, randomVertex2, randomValue);
            listGraph->addDirectedEdge(randomVertex1, randomVertex2, randomValue);

            allEdges->removePair(randomVertex1, randomVertex2); // remove added pair from all pair list

            randomVertex1 = randomVertex2; // set vertex above as next vertex
        }
        verticesList->removeElementFront();// remove last element from list

        // fill list with new vertices
        for (int i = 0; i < vertices; ++i) {
            verticesList->addElement(-1, i);
        }

        // connect first vertex with last to create consistent graph
        matrixGraph->addDirectedEdge(randomVertex2, firstVertex, randomValue);
        listGraph->addDirectedEdge(randomVertex2, firstVertex, randomValue);
        allEdges->removePair(randomVertex1, randomVertex2);
        --wantedEdges;

        while (wantedEdges > 0) {
            ListNode *tempNode;
            int index;
            index = randomNumber(0, allEdges->getSize() - 1);
            tempNode = allEdges->getPair(index);

            randomValue = randomNumber(1, 999);

            matrixGraph->addDirectedEdge(tempNode->neighbour, tempNode->edgeWeight, randomValue);
            listGraph->addDirectedEdge(tempNode->neighbour, tempNode->edgeWeight, randomValue);
            allEdges->removeElementAnywhere(index);
            --wantedEdges;
        }
    } else {
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                allEdges->addElement(i, j);
            }
        }
        wantedEdges /= 2;
        wantedEdges -= edgeCounter;


        while (edgeCounter > 0) {
            while (randomIndex1 == randomIndex2) {
                randomIndex1 = randomNumber(0, verticesList->getSize() - 1);
                randomIndex2 = randomNumber(0, verticesList->getSize() - 1);
            }

            randomVertex1 = verticesList->findValue(randomIndex1);
            randomVertex2 = verticesList->findValue(randomIndex2);

            verticesList->removeElementAnywhere(randomIndex1);

            --edgeCounter;

            randomIndex1 = 0;
            randomIndex2 = 0;
            randomValue = randomNumber(1, 999);

            matrixGraph->addUndirectedEdge(randomVertex1, randomVertex2, randomValue);
            listGraph->addUndirectedEdge(randomVertex1, randomVertex2, randomValue);

            allEdges->removePair(randomVertex1, randomVertex2);
        }

        verticesList->removeElementFront();
        for (int i = 0; i < vertices; ++i) {
            verticesList->addElement(-1, i);
        }

        while (wantedEdges > 0) {
            ListNode *tempNode;
            int index;
            index = randomNumber(0, allEdges->getSize() - 1);
            tempNode = allEdges->getPair(index);

            randomValue = randomNumber(1, 999);

            matrixGraph->addUndirectedEdge(tempNode->neighbour, tempNode->edgeWeight, randomValue);
            listGraph->addUndirectedEdge(tempNode->neighbour, tempNode->edgeWeight, randomValue);

            allEdges->removeElementAnywhere(index);
            --wantedEdges;
        }
    }
    delete allEdges;
    delete verticesList;
}