#include <iostream>
#include <string>
#include <filesystem>

#include "ManualTest.h"
#include "AutomatedTest.h"

using std::cout;
using std::cin;
using std::string;
using namespace std::filesystem;

void createResultsFolders() {
    create_directory("results");
    create_directory("results/array");
    create_directory("results/doubleList");
    create_directory("results/binaryHeap");
    create_directory("results/RBTree");
    create_directory("results/AVLTree");
}

/**
 * Main program body
 * @return
 */
int main() {
    createResultsFolders();
    string textErrorChoice = "Blad, zly wybor\n";
    cout << std::boolalpha; // change bool values to bool words
    bool exit = false;
    bool mainExit = false;
    int input;
    int mainInput;
    while (!mainExit) {
        cout << "0. Wyjscie \n"
                "1. Testy manualne \n"
                "2. Testy automatyczne \n";
        if (!(cin >> mainInput)) { return 0; }
        switch (mainInput) {
            case 0:
                mainExit = true;
                break;
            case 1:
                while (!exit) {
                    cout << "MANUAL TESTS \n"
                            "0. Wyjscie \n"
                            "1. Tablica \n"
                            "2. Lista dwukierunkowa \n"
                            "3. Kopiec binarny \n"
                            "4. Drzewo czerwono-czarne \n"
                            "5. Drzewo AVL \n";
                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            cout << "selected array \n";
                            ManualTest::array();
                            break;
                        case 2:
                            cout << "selected doubleList \n";
                            ManualTest::doubleList();
                            break;
                        case 3:
                            cout << "selected binaryHeap \n";
                            ManualTest::binaryHeap();
                            break;
                        case 4:
                            cout << "selected redBlackTree \n";
                            ManualTest::redBlackTree();
                            break;
                        case 5:
                            cout << "selected avlTree \n";
                            ManualTest::avltree();
                            break;
                        default:
                            cout << textErrorChoice;
                            break;
                    }
                }
                break;
            case 2:
                while (!exit) {
                    cout << "AUTOMATED TESTS \n"
                            "0. Wyjscie \n"
                            "1. Tablica \n"
                            "2. Lista dwukierunkowa \n"
                            "3. Kopiec binarny \n"
                            "4. Drzewo czerwono-czarne \n"
                            "5. Drzewo AVL \n";
                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            cout << "selected array \n";
                            AutomatedTest::array();
                            break;
                        case 2:
                            cout << "selected doubleList \n";
                            AutomatedTest::doubleList();
                            break;
                        case 3:
                            cout << "selected binaryHeap \n";
                            AutomatedTest::binaryHeap();
                            break;
                        case 4:
                            cout << "selected redBlackTree \n";
                            AutomatedTest::redBlackTree();
                            break;
                        case 5:
                            cout << "selected avlTree \n";
                            AutomatedTest::avlTree();
                            break;
                        default:
                            cout << textErrorChoice;
                            break;
                    }
                }
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
    cout << "\n Do widzenia \n";
    return 0;
}