#include <string>
#include <iostream>
#include "ManualTests.h"
#include "Essentials.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

using std::string;
using std::cout;
using std::cin;
using std::exception;

string separator = "\n==============================\n";
string textMenu = separator +
                  "0. Wyjscie\n"
                  "1. Wczytaj graf z pliku\n"
                  "2. Wygeneruj losowy graf\n"
                  "3. Wyswietl graf\n";
string textReadFile = "Podaj nazwe pliku, ktory chcesz wczytac: ";
string textErrorFile = "ERROR, Zla nazwa pliku lub plik nie istnieje\n";
string textErrorChoice = "Blad, zly wybor\n";
string textVerticesCount = "Podaj ilosc wierzcholkow:";
string textDensity = "Podaj gestosc grafu:";
string textStartVertex = "Podaj wierzcholek startowy";
string textEmptyGraph = "Blad, pusty graf\n";
string textErrorValue = "Blad, nieporawna wartosc\n";
int input;
string filename;

void ManualTests::mst() {
    bool exit = false;
    int vertices = 0;
    int density;
    int startVertex;
    int edges;
    int *key = nullptr;
    int *parent = nullptr;
    KruskalEdge **mstEdges;
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);

    while (!exit) {
        cout << textMenu << "4. Wykonaj algorytm Prima\n" << "5. Wykonaj algorytm Kruskala\n" << separator;
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                break;
            case 1:
                cout << textReadFile;
                if (!(cin >> filename)) { return; }
                try {
                    Essentials::getDataFromFile(filename, graphMatrix, graphList, false);
                    vertices = graphList->verticesCount();
                    edges = graphList->getEdges();
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                break;
            case 2:
                cout << textVerticesCount;
                if (!(cin >> vertices)) { return; }
                if (vertices < 2){
                    cout << textErrorValue;
                    vertices = 0;
                    break;
                }
                cout << textDensity;
                if (!(cin >> density)) { return; }
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, false);
                edges = graphList->getEdges();
                break;
            case 3:
                graphMatrix->display();
                graphList->allDisplay();
                break;
            case 4:
                if (vertices == 0) {
                    cout << textEmptyGraph;
                    break;
                }
                cout << textStartVertex << " (max: " << vertices - 1 << "):  ";
                if (!(cin >> startVertex)) { return; }
                if (startVertex < 0 && startVertex >= vertices) {
                    cout << textErrorChoice;
                    break;
                }
                key = new int[vertices];
                parent = new int[vertices];
                Prim::primList(key, parent, startVertex, vertices, graphList);
                Prim::display(key, parent, vertices, "Algorytm Prima jako lista");
                cout << separator;
                Prim::primMatrix(key, parent, startVertex, vertices, graphMatrix);
                Prim::display(key, parent, vertices, "Algorytm Prima jako macierz");
                delete[] key;
                delete[] parent;
                break;
            case 5:
                if (vertices == 0) {
                    cout << textEmptyGraph;
                    break;
                }
                mstEdges = new KruskalEdge *[vertices - 1];
                for (int i = 0; i < vertices - 1; i++) {
                    mstEdges[i] = new KruskalEdge(0, 0, 0);
                }
                Kruskal::kruskalList(mstEdges, vertices, edges, graphList);
                Kruskal::display(mstEdges, vertices, "Algorytm Kruskala jako lista");
                cout << separator;
                Kruskal::kruskalMatrix(mstEdges, vertices, edges, graphMatrix);
                Kruskal::display(mstEdges, vertices, "Algorytm Kruskala jako macierz");
                for (int i = 0; i < vertices - 1; ++i) {
                    delete mstEdges[i];
                }
                delete[] mstEdges;
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
    delete graphMatrix;
    delete graphList;

}

void ManualTests::spf() {
    int vertices = 0;
    int edges;
    int density;
    int startVertex;
    bool exit = false;
    bool cycle;
    int *distance = nullptr;
    int *parent = nullptr;
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    while (!exit) {
        cout << textMenu << "4. Wykonaj algorytm Dijkstry\n" << "5. Wykonaj algorytm Belmana-Forda\n" << separator;
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                break;
            case 1:
                cout << textReadFile;
                if (!(cin >> filename)) { return; }
                try {
                    Essentials::getDataFromFile(filename, graphMatrix, graphList, true);
                    vertices = graphList->verticesCount();
                    edges = graphList->getEdges();
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                break;
            case 2:
                cout << textVerticesCount;
                if (!(cin >> vertices)) { return; }
                if (vertices < 2){
                    cout << textErrorValue;
                    vertices = 0;
                    break;
                }
                cout << textDensity;
                if (!(cin >> density)) { return; }
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, true);
                edges = graphList->getEdges();
                break;
            case 3:
                graphMatrix->display();
                graphList->allDisplay();
                break;
            case 4:
                if (vertices == 0) {
                    cout << textEmptyGraph;
                    break;
                }
                cout << textStartVertex << " (max: " << graphList->verticesCount() - 1 << "):  ";
                if (!(cin >> startVertex)) { return; }
                if (startVertex < 0 && startVertex >= vertices) {
                    cout << textErrorChoice;
                    break;
                }
                distance = new int[vertices];
                parent = new int[vertices];
                Dijkstra::dijkstraList(distance, parent, startVertex, vertices, graphList);
                Dijkstra::display(distance, parent, vertices, "Algorytm Dijkstry jako lista");
                Dijkstra::dijkstraMatrix(distance, parent, startVertex, vertices, graphMatrix);
                Dijkstra::display(distance, parent, vertices, "Algorytm Dijkstry jako macierz");
                delete[] distance;
                delete[] parent;
                break;
            case 5:
                if (vertices == 0) {
                    cout << textEmptyGraph;
                    break;
                }
                cout << textStartVertex << " (max: " << graphList->verticesCount() - 1 << "):  ";
                if (!(cin >> startVertex)) { return; }
                if (startVertex < 0 && startVertex >= vertices) {
                    cout << textErrorChoice;
                    break;
                }
                distance = new int[vertices];
                parent = new int[vertices];
                cycle = BellmanFord::bfList(distance, parent, startVertex, vertices, graphList);
                BellmanFord::display(distance, parent, vertices, cycle, "Algorytm Belmanna-Forda jako lista");
                cycle = BellmanFord::bfMatrix(distance, parent, startVertex, vertices, edges, graphMatrix);
                BellmanFord::display(distance, parent, vertices, cycle, "Algorytm Belmanna-Forda jako macierz");
                delete[] distance;
                delete[] parent;
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
    delete graphMatrix;
    delete graphList;
}

void ManualTests::ffa() {
//TODO
}
