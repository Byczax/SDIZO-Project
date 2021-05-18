#include <iostream>
#include <string>
#include <filesystem>

using std::cout;
using std::cin;
using std::string;
using namespace std::filesystem;

void createResultsFolders() {
    create_directory("results");
    create_directory("results/mstPrim");
    create_directory("results/mstKruskal");
    create_directory("results/pathDijkstra");
    create_directory("results/pathFordBellman");
    create_directory("results/flowFordFulkerson");
}

string textErrorChoice = "Blad, zly wybor\n";
string barrier = "\n==============================\n";

int main() {
    createResultsFolders();

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
                    cout << "\n======= TESTY MANUALNE =======\n"
                            "0. Wyjscie \n"
                            "1. Drzewo rozponajace (MST) - Algorytm Prima\n"
                            "2. Drzewo rozponajace (MST) - Algorytm Kruskala\n"
                            "3. Najkrótsza ścieżka w grafie - Algorytm Dijkstry\n"
                            "4. Najkrótsza ścieżka w grafie - Algorytm Forlda-Bellmana\n"
                            "5. Wyznaczanie maksymalnego przepływu - Algorytm Forda-Fulkersona\n"
                         << barrier << "Twoj wybor: ";

                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default:
                            cout << textErrorChoice;
                            break;
                    }
                }
                break;
            case 2:
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
    cout << barrier << "\nDo widzenia!\n" << barrier;
    return 0;
}