#include <string>
#include <iostream>
#include <fstream>
#include "ManualTests.h"
#include "Essentials.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "AutomatedTests.h"

using std::cout;
using std::string;
using std::ofstream;

int repeat = 10;

int graphSize[] = {20, 40, 60, 80, 100};
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


string strFazaCompleted = "\n==============================\n"
                          "Fazy zakonczone! \n"
                          "==============================\n";

string txt = ".txt";

//void addPercentageCounter(int i, int j) {
//    if (i % (((graphMaxSize) / (graphMinSize))) == 0 && j == 20) {
//        cout << i / (((graphMaxSize) / (graphMinSize))) * 10 << "%\n";
//    }
//}

//template<typename T1, typename T2>
//void testFunctions(string phase, T1 function1, T2 function2, string filename){}

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
//            addPercentageCounter(vertices, density);
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
//            addPercentageCounter(vertices, density);
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
//            addPercentageCounter(vertices, density);
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
//            addPercentageCounter(vertices, density);
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
