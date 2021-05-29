#include <iostream>
#include <string>
#include <filesystem>

#include "ManualTests.h"
#include "AutomatedTests.h"

using std::cout;
using std::cin;
using std::string;
using namespace std::filesystem;

//void createResultsFolders() {
//    create_directory("results");
//    create_directory("results/mstPrim");
//    create_directory("results/mstKruskal");
//    create_directory("results/pathDijkstra");
//    create_directory("results/pathFordBellman");
//    create_directory("results/flowFordFulkerson");
//}

string textErrorChoicea = "Blad, zly wybor\n";
string barrier = "\n==============================\n";
string menu = "0. Wyjscie \n"
              "1. Drzewo rozpinajace (mst)\n"
              "2. Najkrotsza sciezka w grafie (SPF)\n"
              "3. Wyznaczanie maksymalnego przeplywu (FFA)\n" + barrier + "Twoj wybor: ";

void textSelect(const string &selected) {
    cout << barrier << selected << barrier;
}

int main() {
//    createResultsFolders();
    create_directory("results");
    cout << std::boolalpha; // change bool values to bool words

    bool mainExit = false;
    int input;
    while (!mainExit) {
        bool exit = false;
        cout << barrier << "0. Wyjscie \n"
                           "1. Testy manualne \n"
                           "2. Testy automatyczne \n"
             << barrier << "Twoj wybor: ";
        if (!(cin >> input)) { return 0; }
        switch (input) {
            case 0:
                mainExit = true;
                break;
            case 1:
                while (!exit) {
                    cout << "\n======= TESTY MANUALNE =======\n" << menu;
                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            textSelect("Wybrano drzewo rozpinajace (mst)");
                            ManualTests::mst();
                            break;
                        case 2:
                            textSelect("Wybrano wyznaczenie najkrotszej sciezki w grafie (SPF)");
                            ManualTests::spf();
                            break;
                        case 3:
                            textSelect("Wybrano wyznaczanie maksymalnego przepływu (FFA)");
                            cout << "Niestety nie zaimplementowane";
//                            ManualTests::ffa();
                            break;
                        default:
                            cout << textErrorChoicea;
                            break;
                    }
                }
                break;
            case 2:
                while (!exit) {
                    cout << "\n======= TESTY AUTOMATYCZNE =======\n" << menu;
                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            textSelect("Wybrano drzewo rozpinajace (mst)");
                            AutomatedTests::mst();
                            break;
                        case 2:
                            textSelect("Wybrano wyznaczenie najkrotszej sciezki w grafie (SPF)");
                            AutomatedTests::spf();
                            break;
                        case 3:
                            textSelect("Wybrano wyznaczanie maksymalnego przepływu (FFA)");
                            cout << "Niestety nie zaimplementowane";
//                            AutomatedTests::ffa();
                            break;
                        default:
                            cout << textErrorChoicea;
                            break;
                    }
                }
                break;
            default:
                cout << textErrorChoicea;
                break;
        }
    }
    textSelect("\nDo widzenia!\n");
    return 0;
}