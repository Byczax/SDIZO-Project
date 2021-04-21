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

    bool mainExit = false;
    int input;
    while (!mainExit) {
        bool exit = false;
        cout << "\n==============================\n"
                "0. Wyjscie \n"
                "1. Testy manualne \n"
                "2. Testy automatyczne \n"
                "==============================\n"
                "Twoj wybor: ";
        if (!(cin >> input)) { return 0; }
        switch (input) {
            case 0:
                mainExit = true;
                break;
            case 1:
                while (!exit) {
                    cout << "\n======= MANUAL TESTS ========\n"
                            "0. Wyjscie \n"
                            "1. Tablica \n"
                            "2. Lista dwukierunkowa \n"
                            "3. Kopiec binarny \n"
                            "4. Drzewo czerwono-czarne \n"
                            "5. Drzewo AVL \n"
                            "==============================\n"
                            "Twoj wybor: ";

                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            cout << "\n==============================\n"
                                    "selected array \n"
                                    "==============================\n";
                            ManualTest::array();
                            break;
                        case 2:
                            cout << "\n==============================\n"
                                    "selected doubleList \n"
                                    "==============================\n";
                            ManualTest::doubleList();
                            break;
                        case 3:
                            cout << "\n==============================\n"
                                    "selected binaryHeap \n"
                                    "==============================\n";
                            ManualTest::binaryHeap();
                            break;
                        case 4:
                            cout << "\n==============================\n"
                                    "selected redBlackTree \n"
                                    "==============================\n";
                            ManualTest::redBlackTree();
                            break;
                        case 5:
                            cout << "\n==============================\n"
                                    "selected avlTree \n"
                                    "==============================\n";
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
                    cout << "\n====== AUTOMATED TESTS =======\n"
                            "0. Wyjscie \n"
                            "1. Tablica \n"
                            "2. Lista dwukierunkowa \n"
                            "3. Kopiec binarny \n"
                            "4. Drzewo czerwono-czarne \n"
                            "5. Drzewo AVL \n"
                            "==============================\n"
                            "Twoj wybor: ";

                    if (!(cin >> input)) { return 0; }
                    switch (input) {
                        case 0:
                            exit = true;
                            break;
                        case 1:
                            cout << "\n==============================\n"
                                    "selected array \n"
                                    "==============================\n";
                            AutomatedTest::array();
                            break;
                        case 2:
                            cout << "\n==============================\n"
                                    "selected doubleList \n"
                                    "==============================\n";
                            AutomatedTest::doubleList();
                            break;
                        case 3:
                            cout << "\n==============================\n"
                                    "selected binaryHeap \n"
                                    "==============================\n";
                            AutomatedTest::binaryHeap();
                            break;
                        case 4:
                            cout << "\n==============================\n"
                                    "selected redBlackTree \n"
                                    "==============================\n";
                            AutomatedTest::redBlackTree();
                            break;
                        case 5:
                            cout << "\n==============================\n"
                                    "selected avlTree \n"
                                    "==============================\n";
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
    cout << "\n==============================\n"
            "\n Do widzenia \n"
            "==============================\n";
    return 0;
}