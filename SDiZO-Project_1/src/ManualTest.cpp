#include <string>
#include <chrono>

#include "Array.h"
#include "DoubleList.h"
#include "BinaryHeap.h"
#include "RedBlackTree.h"
#include "AVLTree.h"
#include "ManualTest.h"
#include "Essentials.h"


using std::string;
using std::cout;
using std::cin;
using std::exception;

// Global strings to removeValue repetition and cleanup code
string textGetValue = "Podaj wartosc ktora chcesz dodac: ";
string textRemoveValue = "Podaj wartosc ktora chcesz usunac: ";
string textGetIndex = "Podaj pozycje na ktora chcesz dodac element: ";
string textRemoveIndex = "Podaj pozycje ktora chcesz usunac: ";
string textFindValue = "Podaj wartosc ktora chcesz znalezc: ";
string textReadFile = "Podaj nazwe pliku, ktory chcesz wczytac: ";
string textDataAmount = "Podaj ile chcesz danych: ";
string textOperation = "Czas wykonania operacji: ";
string textErrorFile = "ERROR, Zla nazwa pliku lub plik nie istnieje\n";
string deleteErrorChoice = "Blad, nie ma takiego elementu\n";
string textErrorChoice = "Blad, zly wybor\n";
string separator = "==============================\n";

void ManualTest::array() {
    auto *array = new Array(); // Create empty array
    bool exit = false;
    int input;
    int value;
    int *data;
    int temp;
    bool exist;
    string filename;
    unsigned int index;
    while (!exit) {
        cout << "\n==============================\n"
                "0. Wyjscie \n"
                "1. Stworz nowa pusta tablice \n"
                "2. Stworz tablice z pliku \n"
                "3. Stworz tablice z losowych danych \n"
                "4. Dodaj element z przodu \n"
                "5. Dodaj element z tylu \n"
                "6. Dodaj element gdziekolwiek \n"
                "7. Usun element z przodu \n"
                "8. Usun element z tylu \n"
                "9. Usun element gdziekolwiek \n"
                "10. Usun wartosc (jezeli istnieje) \n"
                "11. Znajdz element \n"
                "12. Wyswietl zawartosc \n"
             << separator <<
             "Twoj wybor: ";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                delete array;
                break;
            case 1:
                // Create new empty array
                delete array;
                array = new Array();
                break;
            case 2:
                // Create new array from the value in the file
                cout << textReadFile;
                if (!(cin >> filename)) { return; }
                try {
                    data = Essentials::getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete array;
                array = new Array(data + 1, data[0]);
                break;
            case 3:
                // Create new array from random value
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                delete array;
                data = Essentials::randomData(value);
                array = new Array(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                // Add an element to the front of the array
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { array->addElementFront(value); }) << "\n";
                break;
            case 5:
                // Add an element to the back of the array
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { array->addElementBack(value); }) << "\n";
                break;
            case 6:
                // Add an element anywhere in the array
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textGetIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { array->addElementAnywhere(value, index); }) << "\n";
                break;
            case 7:
                // Remove an element from the front in the array
                cout << textOperation << Timer([&] { exist = array->removeElementFront(); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 8:
                // Remove an element from the back in the array
                cout << textOperation << Timer([&] { exist = array->removeElementBack(); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 9:
                // Remove an element anywhere in the array
                cout << textRemoveIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { exist = array->removeElementAnywhere(index); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 10:
                // Remove value from the array
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { exist = array->removeValue(value); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 11:
                // Find value in the array
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { temp = array->findValue(value); }) << "\n";
                if (temp != -1) {
                    cout << "\n==============================\n"
                            "Znaleziona wartosc znajduje sie pod: " << temp << "\n"
                         << separator;
                } else {
                    cout << deleteErrorChoice;
                }
                break;
            case 12:
                // Display array in the console
                array->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

void ManualTest::doubleList() {
    auto list = new DoubleList(nullptr, 0);// Create empty doubleList
    bool exit = false;
    int input;
    int value;
    int *data = nullptr;
    int temp;
    bool exist;
    string filename;
    unsigned int index;
    while (!exit) {
        cout << "\n==============================\n"
                "0. Wyjscie \n"
                "1. Stworz nowa pusta liste \n"
                "2. Stworz nowa liste z danych z pliku \n"
                "3. Stworz nowa liste z losowych danych \n"
                "4. Dodaj element z przodu \n"
                "5. Dodaj element z tylu \n"
                "6. Dodaj element gdziekolwiek \n"
                "7. Usun element z przodu \n"
                "8. Usun element z tylu \n"
                "9. Usun element gdziekolwiek \n"
                "10. Usun wartosc (jezeli istnieje) \n"
                "11. Znajdz element \n"
                "12. Wyswietl zawartosc \n"
             << separator <<
             "Twoj wybor: ";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                delete list;
                break;
            case 1:
                // Create new empty doubleList
                delete list;
                list = new DoubleList(nullptr, 0);
                break;
            case 2:
                // Create new doubleList from the value in the file
                cout << textReadFile;
                if (!(cin >> filename)) { return; }
                try {
                    data = Essentials::getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete list;
                list = new DoubleList(data + 1, data[0]);
                break;
            case 3:
                // Create new doubleList from random value
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                delete list;
                data = Essentials::randomData(value);
                list = new DoubleList(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                // Add an element to the front of the doubleList
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { list->addElementFront(value); }) << "\n";
                break;
            case 5:
                // Add an element to the back of the doubleList
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { list->addElementBack(value); }) << "\n";
                break;
            case 6:
                // Add an element anywhere in the doubleList
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textGetIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { list->addElementAnywhere(value, index); }) << "\n";
                break;
            case 7:
                // Remove an element from the front of the doubleList
                cout << textOperation << Timer([&] { exist = list->removeElementFront(); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 8:
                // Remove an element from the back of the doubleList
                cout << textOperation << Timer([&] { exist = list->removeElementBack(); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 9:
                // Remove an element anywhere in the doubleList
                cout << textRemoveIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { exist = list->removeElementAnywhere(index); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 10:
                // Remove value from the doubleList
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { exist = list->removeValue(value); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 11:
                // strFind value from the doubleList
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { temp = list->findValue(value); }) << "\n";
                if (temp >= 0) {
                    cout << "Znaleziona wartosc znajduje sie pod: " << temp << "\n";
                } else {
                    cout << deleteErrorChoice;
                }

                break;
            case 12:
                // Display doubleList
                list->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

void ManualTest::binaryHeap() {
    auto heap = new BinaryHeap(nullptr, 0);
    bool exit = false;
    int input;
    int value;
    int intTemp;
    bool exist;
    string filename;
    while (!exit) {
        cout << "\n==============================\n"
                "0. Wyjscie \n"
                "1. Stworz nowy pusty kopiec \n"
                "2. Stworz nowy kopiec z danych z pliku \n"
                "3. Stworz nowy kopiec z losowych danych \n"
                "4. Dodaj wartosc \n"
                "5. Usun wartosc (jezeli istnieje) \n"
                "6. Znajdz element \n"
                "7. Wyswietl kopiec \n"
             << separator <<
             "Twoj wybor: ";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                delete heap;
                break;
            case 1:
                // create new empty binaryHeap
                delete heap;
                heap = new BinaryHeap(nullptr, 0);
                break;
            case 2:
                // Create new binaryHeap from the value in the file
                cout << textReadFile;
                int *data;
                if (!(cin >> filename)) { return; }
                try {
                    data = Essentials::getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete heap;
                heap = new BinaryHeap(data + 1, data[0]);
                break;
            case 3:
                // Create new binaryHeap from random value
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                data = Essentials::randomData(value);
                delete heap;
                heap = new BinaryHeap(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                // Add an element to binaryHeap
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { heap->addValue(value); }) << "\n";
                break;
            case 5:
                // Remove value from the binaryHeap
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] {exist = heap->removeValue(value); }) << "\n";
                if (!exist) {
                    cout << deleteErrorChoice;
                }
                break;
            case 6:
                // Find element in the binaryHeap
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { intTemp = heap->findValue(value); }) << "\n";
                if (intTemp >= 0) {
                    cout << true << "\n";
                } else {
                    cout << false << "\n";
                }
                break;
            case 7:
                // Display binaryHeap in the console
                heap->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}


void ManualTest::redBlackTree() {
    auto tree = new RedBlackTree(nullptr, 0);
    bool exit = false;
    int input;
    int value;
    bool temp;
    string filename;
    while (!exit) {
        cout << "\n==============================\n"
                "0. Wyjscie \n"
                "1. Stworz nowe puste drzewo \n"
                "2. Stworz nowe drzewo z danych z pliku \n"
                "3. Stworz nowe drzewo z losowych danych \n"
                "4. Dodaj wartosc \n"
                "5. Usun wartosc (jezeli istnieje) \n"
                "6. Znajdz element \n"
                "7. Wyswietl drzewo \n"
             << separator <<
             "Twoj wybor: ";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                delete tree;
                exit = true;
                break;
            case 1:
                delete tree;
                tree = new RedBlackTree(nullptr, 0);
                break;
            case 2:
                // Create new redBlackTree from the value in the file
                cout << textReadFile;
                int *data;
                if (!(cin >> filename)) { return; }
                try {
                    data = Essentials::getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete tree;
                tree = new RedBlackTree(data + 1, data[0]);
                break;
            case 3:
                // Create new binaryHeap from random value
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                data = Essentials::randomData(value);
                delete tree;
                tree = new RedBlackTree(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { tree->addValue(value); }) << "\n";
                break;
            case 5:
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { tree->removeValue(value); }) << "\n";
                break;
            case 6:
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { temp = tree->findValue(value); }) << "\n";
                cout << temp << "\n";
                break;
            case 7:
                tree->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}


void ManualTest::avltree() {
    auto avlTree = new AVLTree(nullptr, 0);
    bool exit = false;
    int input;
    int value;
    bool find;
    string filename;
    while (!exit) {
        cout << "\n==============================\n"
                "0. Wyjscie \n"
                "1. Stworz nowe puste drzewo \n"
                "2. Stworz nowe drzewo z danych z pliku \n"
                "3. Stworz nowe drzewo z losowych danych \n"
                "4. Dodaj wartosc \n"
                "5. Usun wartosc (jezeli istnieje) \n"
                "6. Znajdz element \n"
                "7. Wyswietl drzewo \n"
             << separator <<
             "Twoj wybor: ";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                delete avlTree;
                exit = true;
                break;
            case 1:
                delete avlTree;
                avlTree = new AVLTree(nullptr, 0);
                break;
            case 2:
                // Create new avlTree from the value in the file
                cout << textReadFile;
                int *data;
                if (!(cin >> filename)) { return; }
                try {
                    data = Essentials::getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete avlTree;
                avlTree = new AVLTree(data + 1, data[0]);
                break;
            case 3:
                // Create new binaryHeap from random value
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                data = Essentials::randomData(value);
                delete avlTree;
                avlTree = new AVLTree(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { avlTree->addValue(value); }) << "\n";
                break;
            case 5:
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { avlTree->removeValue(value); }) << "\n";
                break;
            case 6:
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { find = avlTree->findValue(value); }) << "\n";
                if (find) {
                    cout << true << "\n";
                } else {
                    cout << false << "\n";
                }
                break;
            case 7:
                avlTree->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}
