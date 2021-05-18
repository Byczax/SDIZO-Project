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

void textSelect(const string& selected){
    cout << barrier << selected << barrier;
}

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
                            "1. Drzewo rozpinajace (MST) - Algorytm Prima\n"
                            "2. Drzewo rozpinajace (MST) - Algorytm Kruskala\n"
                            "3. Najkrótsza ścieżka w grafie (SPF) - Algorytm Dijkstry\n"
                            "4. Najkrótsza ścieżka w grafie (SPF) - Algorytm Forlda-Bellmana\n"
                            "5. Wyznaczanie maksymalnego przepływu (FFA) - Algorytm Forda-Fulkersona\n"
                         << barrier << "Twoj wybor: ";

                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            textSelect("Wybrano drzewo rozpinajace (MST) - Algorytm Prima");
                            break;
                        case 2:
                            textSelect("Wybrano drzewo rozpinajace (MST) - Algorytm Kruskala");
                            break;
                        case 3:
                            textSelect("Wybrano wyznaczenie najkrótszej ścieżki w grafie (SPF) - Algorytm Dijkstry");
                            break;
                        case 4:
                            textSelect("Wybrano wyznaczenie najkrótszej ścieżki w grafie (SPF) - Algorytm Forda-Bellmana");
                            break;
                        case 5:
                            textSelect("Wybrano wyznaczanie maksymalnego przepływu (FFA) - Algorytm Forda-Fulkersona");
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