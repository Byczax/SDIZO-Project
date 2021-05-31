#include <string>
#include <iostream>
#include <fstream>
#include "Essentials.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "AutomatedTests.h"

using std::cout;
using std::string;
using std::ofstream;

int repeat = 100;

int graphSize[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
int graphDensity[] = {25, 50, 75, 99};

int graphSizeMin = 20;
int graphSizeMax = 100;

int graphDensityMin = 25;
int graphDensityMax = 99;


string strResultsPrim = "results/Prim";
string strResultsKruskal = "results/Kruskal";
string strResultsDijkstra = "results/Dijkstra";
string strResultsBellmanFord = "results/BellmanFord";
string strResultsFordFulkerson = "results/FordFulkerson";

string strPhasePrim = "\n==============================\n"
                      "Faza Prima\n"
                      "==============================\n";
string strPhaseKruskal = "\n==============================\n"
                         "Faza Kruskala\n"
                         "==============================\n";
string strPhaseDijkstra = "\n==============================\n"
                          "Faza Dijkstry\n"
                          "==============================\n";
string strPhaseBellmanFord = "\n==============================\n"
                             "Faza Bellmana-Forda\n"
                             "==============================\n";
string strPhaseFordFulkerson = "\n==============================\n"
                               "Faza Forda-Fulkersona\n"
                               "==============================\n";

string txt = ".txt";

void AutomatedTests::mstPrim() {
    cout << strPhasePrim;
    ofstream file;
    file.open(strResultsPrim + txt);
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    int *key = nullptr;
    int *parent = nullptr;
    cout << "0%\n";
    for (int vertices:graphSize) {
        for (int density:graphDensity) {
            for (int i = 0; i < repeat; ++i) {

                key = new int[vertices];
                parent = new int[vertices];
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, false);
                file << vertices << "," << density << ","
                     << Timer([&] { Prim::primList(key, parent, 0, vertices, graphList); }) << ","
                     << Timer([&] { Prim::primMatrix(key, parent, 0, vertices, graphMatrix); }) << "\n";
                delete[] key;
                delete[] parent;
            }
        }
    }
    delete graphMatrix;
    delete graphList;
    file.close();
    cout << "100%\n";
}

void AutomatedTests::mstKruskal() {
    cout << strPhaseKruskal;
    ofstream file;
    file.open(strResultsKruskal + txt);
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    int edges;
    KruskalEdge **mstEdges;
    for (int vertices:graphSize) {
        for (int density:graphDensity) {
            for (int i = 0; i < repeat; ++i) {
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, false);
                edges = graphList->getEdges();
                mstEdges = new KruskalEdge *[vertices - 1];
                for (int ii = 0; ii < vertices - 1; ii++) {
                    mstEdges[ii] = new KruskalEdge(0, 0, 0);
                }
                file << vertices << "," << density << ","
                     << Timer([&] { Kruskal::kruskalList(mstEdges, vertices, edges, graphList); }) << ","
                     << Timer([&] { Kruskal::kruskalMatrix(mstEdges, vertices, edges, graphMatrix); }) << "\n";
            }
        }
    }
    delete graphMatrix;
    delete graphList;
    file.close();
}

void AutomatedTests::spfDijkstra() {
    cout << strPhaseDijkstra;
    ofstream file;
    file.open(strResultsDijkstra + txt);
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    int *distance = nullptr;
    int *parent = nullptr;
    for (int vertices:graphSize) {
        for (int density:graphDensity) {
            for (int i = 0; i < repeat; ++i) {
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, true);
                distance = new int[vertices];
                parent = new int[vertices];
                file << vertices << "," << density << ","
                     << Timer([&] { Dijkstra::dijkstraList(distance, parent, 0, vertices, graphList); }) << ","
                     << Timer([&] { Dijkstra::dijkstraMatrix(distance, parent, 0, vertices, graphMatrix); }) << "\n";
            }
        }
    }
    delete graphMatrix;
    delete graphList;
    file.close();
}

void AutomatedTests::spfBellmanFord() {
    cout << strPhaseBellmanFord;
    ofstream file;
    file.open(strResultsBellmanFord + txt);
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    int *distance = nullptr;
    int *parent = nullptr;
    int edges = 0;
    for (int vertices:graphSize) {
        for (int density:graphDensity) {
            for (int i = 0; i < repeat; ++i) {
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, true);
                distance = new int[vertices];
                parent = new int[vertices];
                edges = graphList->getEdges();
                file << vertices << "," << density << ","
                     << Timer([&] { BellmanFord::bfList(distance, parent, 0, vertices, graphList); }) << ","
                     << Timer([&] { BellmanFord::bfMatrix(distance, parent, 0, vertices, edges, graphMatrix); })
                     << "\n";
            }
        }
    }
    delete graphMatrix;
    delete graphList;
    file.close();
}

void AutomatedTests::mst() {
    mstPrim();
    mstKruskal();
}

void AutomatedTests::spf() {
    spfDijkstra();
    spfBellmanFord();
}

void AutomatedTests::ffa() {
}
