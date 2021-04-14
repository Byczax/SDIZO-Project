#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include <chrono>

#include "DoubleList.h"
#include "Array.h"
#include "BinaryHeap.h"
#include "RedBlackTree.h"
#include "AVLTree.h"

using namespace std;

// Global strings to remove repetition and cleanup code
string textGetValue = "Podaj wartosc ktora chcesz dodac: ";
string textRemoveValue = "Podaj wartosc ktora chcesz usunac: ";
string textGetIndex = "Podaj pozycje na ktora chcesz dodac element: ";
string textRemoveIndex = "Podaj pozycje ktora chcesz usunac: ";
string textFindValue = "Podaj wartosc ktora chcesz znalezc: ";
string textFindIndex = "Podaj pozycje ktora chcesz wyswietlic: ";
string textErrorFile = "ERROR, Zla nazwa pliku lub plik nie istnieje";
string textReadFile = "Podaj nazwe pliku, ktory chcesz wczytac: ";
string textErrorChoice = "Blad, zly wybor";
string textDataAmount = "Podaj ile chcesz danych: ";
string textOperation = "Czas wykonania operacji: ";
//-----------------------Time counter----------------------------------------------------------
// Only windows, need windows.h
/**
 * code fragment from https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
 * responsible for the preparation of QueryPerformanceCounter and methods for measuring time
 */
//double PCFreq = 0.0;
//__int64 CounterStart = 0;

/**
 * Start time counter
 */
//void StartCounter() {
//    LARGE_INTEGER li;
//    if (!QueryPerformanceFrequency(&li))
//        cout << "QueryPerformanceFrequency failed!\n";
//
//    PCFreq = double(li.QuadPart) / 1000.0;
//
//    QueryPerformanceCounter(&li);
//    CounterStart = li.QuadPart;
//}

/**
 * Stop time counter
 * @return
 */
//double GetCounter() {
//    LARGE_INTEGER li;
//    QueryPerformanceCounter(&li);
//    return double(li.QuadPart - CounterStart) / PCFreq;
//}

/**
 * Lambda to get runtime
 * @tparam T
 * @param i
 * @return
 */
//template<typename T>
//double Timer(T i) {
//    StartCounter();
//    i();
//    return GetCounter();
//}
//----------------------------------------------------------------------------------------------
/**
 * Counter for all systems
 * @tparam T
 * @param i
 * @return
 */
template<typename T>
double Timer(T i) {
    auto start = chrono::high_resolution_clock::now();// Start the counter
    i();// our function
    auto end = chrono::high_resolution_clock::now();// Get value after executing function
    auto duration = end - start;// get time difference
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(duration).count();// calculate time
    return elapsed_time;// Return executing time in nanoseconds
}


/**
 * Generate random data
 * @param amount
 * @return
 */
int *randomData(int amount) {
    int *data_table = new int[amount + 1];
    data_table[0] = amount;
    for (int i = 1; i < amount + 1; ++i) {
        data_table[i] = rand();
    }
    return data_table;
}

/**
 * Read data from file
 * @param filename
 * @return
 */
int *getDataFromFile(const string &filename) {
    fstream file;
    file.open(filename, ios::in);
    int *array;
    string str;
    int number;
    if (file) {
        getline(file, str);
        number = stoi(str);
        array = new int[number + 1];
        array[0] = number;
        unsigned int i = 1;
        while (!file.eof()) {
            getline(file, str);
            number = stoi(str);
            array[i] = number;
            ++i;
        }
        file.close();
        return array;
    } else throw exception();
}

void myArray() {
    auto *array = new Array(nullptr, 0); // Create empty array
    bool exit = false;
    int input;
    int value;
    int *data;
    int temp;
    string filename;
    unsigned int index;
    while (!exit) {
        cout << "0. Wyjscie \n"
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
                "12. Wyswietl wartosc pod indeksem \n"
                "13. Wyswietl zawartosc \n";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                delete array;
                break;
            case 1:
                // Create new empty array
                delete array;
                array = new Array(nullptr, 0);
                break;
            case 2:
                // Create new array from the data in the file
                cout << textReadFile;
                if (!(cin >> filename)) { return; }
                try {
                    data = getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete array;
                array = new Array(data + 1, data[0]);
                break;
            case 3:
                // Create new array from random data
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                delete array;
                data = randomData(value);
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
                cout << textOperation << Timer([&] { array->removeElementFront(); }) << "\n";
                break;
            case 8:
                // Remove an element from the back in the array
                cout << textOperation << Timer([&] { array->removeElementBack(); }) << "\n";
                break;
            case 9:
                // Remove an element anywhere in the array
                cout << textRemoveIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { array->removeElementAnywhere(index); }) << "\n";
                break;
            case 10:
                // Remove value from the array
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { array->removeValue(value); }) << "\n";
                break;
            case 11:
                // Find value in the array
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { temp = array->findValue(value); }) << "\n";
                if (temp != -1) {
                    cout << "Znaleziona wartosc znajduje sie pod: " << temp << "\n";
                } else {
                    cout << "Nie ma takiej wartosci" << "\n";
                }
                break;
            case 12:
                // Get value under given index in the array
                cout << textFindIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { temp = array->getIndexValue(index); }) << "\n";
                cout << "Wartosc pod indeksem: " << temp << "\n";
                break;
            case 13:
                // Display array in the console
                array->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

void doubleList() {
    auto list = new DoubleList(nullptr, 0);// Create empty list
    bool exit = false;
    int input;
    int value;
    int *data = nullptr;
    ListNode *temp = nullptr;
    string filename;
    unsigned int index;
    while (!exit) {
        cout << "0. Wyjscie \n"
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
                "12. Wyswietl zawartosc \n";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                delete list;
                break;
            case 1:
                // Create new empty list
                delete list;
                list = new DoubleList(nullptr, 0);
                break;
            case 2:
                // Create new list from the data in the file
                cout << textReadFile;
                if (!(cin >> filename)) { return; }
                try {
                    data = getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete list;
                list = new DoubleList(data + 1, data[0]);
                break;
            case 3:
                // Create new list from random data
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                delete list;
                data = randomData(value);
                list = new DoubleList(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                // Add an element to the front of the list
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { list->addElementFront(value); }) << "\n";
                break;
            case 5:
                // Add an element to the back of the list
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { list->addElementBack(value); }) << "\n";
                break;
            case 6:
                // Add an element anywhere in the list
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textGetIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { list->addElementAnywhere(value, index); }) << "\n";
                break;
            case 7:
                // Remove an element from the front of the list
                cout << textOperation << Timer([&] { list->removeElementFront(); }) << "\n";
                break;
            case 8:
                // Remove an element from the back of the list
                cout << textOperation << Timer([&] { list->removeElementBack(); }) << "\n";
                break;
            case 9:
                // Remove an element anywhere in the list
                cout << textRemoveIndex;
                if (!(cin >> index)) { return; }
                cout << textOperation << Timer([&] { list->removeElementAnywhere(index); }) << "\n";
                break;
            case 10:
                // Remove value from the list
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { list->removeValue(value); }) << "\n";
                break;
            case 11:
                // find value from the list
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { temp = list->findValue(value); }) << "\n";
                cout << (temp != nullptr) << "\n";
                break;
            case 12:
                // Display list
                list->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

void binaryHeap() {
    cout << "W implementacji\n";
    auto heap = new BinaryHeap(nullptr, 0);
    bool exit = false;
    int input;
    int value;
    int intTemp;
    string filename;
    while (!exit) {
        cout << "0. Wyjscie \n"
                "1. Stworz nowy pusty kopiec \n"
                "2. Stworz nowy kopiec z danych z pliku \n"
                "3. Stworz nowy kopiec z losowych danych \n"
                "4. Dodaj wartosc \n"
                "5. Usun wartosc (jezeli istnieje) \n"
                "6. Znajdz element \n"
                "7. Wyswietl kopiec \n";
        if (!(cin >> input)) { return; }
        switch (input) {
            case 0:
                exit = true;
                delete heap;
                break;
            case 1:
                // create new empty heap
                delete heap;
                heap = new BinaryHeap(nullptr, 0);
                break;
            case 2:
                // Create new heap from the data in the file
                cout << textReadFile;
                int *data;
                if (!(cin >> filename)) { return; }
                try {
                    data = getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete heap;
                heap = new BinaryHeap(data + 1, data[0]);
                break;
            case 3:
                // Create new heap from random data
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                data = randomData(value);
                delete heap;
                heap = new BinaryHeap(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                // Add an element to heap
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { heap->addElement(value); }) << "\n";
                break;
            case 5:
                // Remove value from the heap
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { heap->removeValue(value); }) << "\n";
                break;
            case 6:
                // Find element in the heap
                cout << textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { intTemp = heap->findValue(value); }) << "\n";
                if (!intTemp) {
                    cout << intTemp << "\n";
                } else {
                    cout << false << "\n";
                }
                break;
            case 7:
                // Display heap in the console
                heap->display();
                break;
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

//TODO Red-Black Tree
void tree() {
    cout << "W implementacji\n";
    auto tree = new RedBlackTree(nullptr, 0);
    bool exit = false;
    int input;
    int value;
    string filename;
    while (!exit) {
        cout << "0. Wyjscie \n"
                "1. Stworz nowe puste drzewo \n"
                "2. Stworz nowe drzewo z danych z pliku \n"
                "3. Stworz nowe drzewo z losowych danych \n"
                "4. Dodaj wartosc \n"
                "5. Usun wartosc (jezeli istnieje) \n"
                "6. Znajdz element \n"
                "7. Wyswietl drzewo \n";
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
                // Create new tree from the data in the file
                cout << textReadFile;
                int *data;
                if (!(cin >> filename)) { return; }
                try {
                    data = getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete tree;
                tree = new RedBlackTree(data + 1, data[0]);
                break;
            case 3:
                // Create new heap from random data
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                data = randomData(value);
                delete tree;
                tree = new RedBlackTree(data + 1, data[0]);
                delete[] data;
                break;
            case 4:
                cout << textGetValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { tree->addElement(value); }) << "\n";
                break;
            case 5:
                cout << textRemoveValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { tree->removeValue(value); }) << "\n";
                break;
            case 6:
                cout <<textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { tree->findGivenNumber(value); }) << "\n";
                break;
            case 7:
                tree->display();
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

//TODO AVL???
void avltree() {
    cout << "W implementacji\n";
    auto avlTree = new AVLTree(nullptr, 0);
    bool exit = false;
    int input;
    int value;
    string filename;
    while (!exit) {
        cout << "0. Wyjscie \n"
                "1. Stworz nowe puste drzewo \n"
                "2. Stworz nowe drzewo z danych z pliku \n"
                "3. Stworz nowe drzewo z losowych danych \n"
                "4. Dodaj wartosc \n"
                "5. Usun wartosc (jezeli istnieje) \n"
                "6. Znajdz element \n"
                "7. Wyswietl drzewo \n";
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
                // Create new avlTree from the data in the file
                cout << textReadFile;
                int *data;
                if (!(cin >> filename)) { return; }
                try {
                    data = getDataFromFile(filename);
                }
                catch (exception &e) {
                    cout << textErrorFile;
                    break;
                }
                delete avlTree;
                avlTree = new AVLTree(nullptr, 0);
                break;
            case 3:
                // Create new heap from random data
                cout << textDataAmount;
                if (!(cin >> value)) { return; }
                data = randomData(value);
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
                cout <<textFindValue;
                if (!(cin >> value)) { return; }
                cout << textOperation << Timer([&] { avlTree->findValue(value); }) << "\n";
                break;
            case 7:
                avlTree->display2();
            default:
                cout << textErrorChoice;
                break;
        }
    }
}

/**
 * Main program body
 * @return
 */
int main() {
    setlocale(LC_ALL, ""); // attempt to repair Polish characters
    cout << boolalpha; // change bool values to bool words
    bool exit = false;
    int input;
    while (!exit) {
        cout << "0. Wyjscie \n"
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
                myArray();
                break;
            case 2:
                doubleList();
                break;
            case 3:
                binaryHeap();
                break;
            case 4:
                tree();
                break;
            case 5:
                avltree();
            default:
                cout << textErrorChoice;
                break;
        }
    }
    cout << "\nDo widzenia\n";
    return 0;
}