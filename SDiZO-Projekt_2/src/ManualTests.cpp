#include <string>
#include <iostream>
#include "ManualTests.h"
#include "Essentials.h"
#include "Prim.h"

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
string textVerticesCount = "Podaj ilosc wierzcholkow:  ";
string textDensity = "Podaj gestosc grafu:  ";
string textStartVertex = "Podaj wierzcholek startowy";

int input;
string filename;

void ManualTests::mst() {
    //TODO
    bool exit = false;
    int vertices;
    int density;
    int startVertex;
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    while (!exit) {
        cout << textMenu << "4.Wykonaj algorytm Prima\n" << "5.Wykonaj algorytm Kruskala\n" << separator;
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
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                break;
            case 2:
                cout << textVerticesCount;
                if (!(cin >> vertices)) { return; }
                cout << textDensity;
                if (!(cin >> density)) { return; }
                Essentials::generateRandomGraph(vertices, density, graphMatrix, graphList, false);
                break;
            case 3:
                graphMatrix->display();
                graphList->allDisplay();
                break;
            case 4:
                cout << textStartVertex << " (max: "<<vertices<<"):  ";
                if (!(cin >> startVertex)) { return; }
                int *key = new int[vertices];
                int *parent = new int[vertices];
                Prim::primList(key, parent, startVertex, graphList);
                Prim::primMatrix(key, parent, startVertex, graphMatrix);

                break;
            case 5:
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
//TODO
    bool exit = false;
    auto *graphMatrix = new Matrix();
    auto *graphList = new AdjacencyList(0, 0);
    while (!exit) {
        cout << textMenu << "4.Wykonaj algorytm Dijkstry\n" << "5.Wykonaj algorytm Belmana-Forda\n" << separator;
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
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                break;
            case 2:
                break;
            case 3:
                graphMatrix->display();
                graphList->allDisplay();
                break;
            case 4:
                cout << textStartVertex << " (max: "<<graphList->verticesCount()<<"):  ";
                break;
            case 5:
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
