#include <chrono>
#include <fstream>
#include "AutomatedTest.h"
#include "DoubleList.h"
#include "Array.h"
#include "BinaryHeap.h"
#include "RedBlackTree.h"
#include "AVLTree.h"
#include "Essentials.h"

using std::cout;
using std::string;
using std::ofstream;

int startElementQuantity = 10; // best value is 1000
int stopElementQuantity = 100; // best value is 50000
int *data;

void addCounter(int i) {
    if (i % ((stopElementQuantity / startElementQuantity) * 100) == 0) {
        cout << i / ((stopElementQuantity / startElementQuantity) * 100) * 10 << "%\n";
    }
}

void removeCounter(int i) {
    if (i % ((stopElementQuantity / startElementQuantity) * 100) == 0) {
        cout << (stopElementQuantity - i) / (stopElementQuantity / startElementQuantity) / 10 + 10 << "%\n";
    }
}


template<typename T1, typename T2>
void testAdding(string phase, T1 function, string filename, T2 findFunction, ofstream &findFile) {
    ofstream file;
    file.open(filename);
    cout << phase;
    for (int i = startElementQuantity; i <= stopElementQuantity; ++i) {
        addCounter(i);
        file << i << "," << Timer([&] { function(); }) << "\n";
        findFile << i << "," << Timer([&] { findFunction(); }) << "\n";
    }
    file.close();
}

template<typename T1, typename T2>
void testRemoving(string phase, T1 function, string filename, T2 findFunction, ofstream &findFile) {
    ofstream file;
    file.open(filename);
    cout << phase;
    for (int i = stopElementQuantity; i >= startElementQuantity; --i) {
        removeCounter(i);
        file << i << "," << Timer([&] { function(); }) << "\n";
        findFile << i << "," << Timer([&] { findFunction(); }) << "\n";
    }
    file.close();
}

template<typename T>
void addFrontFunction(T structure, string filename, ofstream &findFile) {
    testAdding(
            "\n==============================\n"
            "phase 1. adding elements front \n"
            "==============================\n",
            [&] { structure->addElementFront(Essentials::randomValue()); },
            filename,
            [&] { structure->findValue(Essentials::randomValue()); },
            findFile);
}

template<typename T>
void removeFrontFunction(T structure, string filename, ofstream &findFile) {
    testRemoving(
            "\n==============================\n"
            "phase 2. removing elements front \n"
            "==============================\n",
            [&] { structure->removeElementFront(); },
            filename,
            [&] { structure->findValue(Essentials::randomValue()); },
            findFile);
}

template<typename T>
void addBackFunction(T structure, string filename, ofstream &findFile) {
    testAdding(
            "\n==============================\n"
            "phase 3. adding elements back \n"
            "==============================\n",
            [&] { structure->addElementBack(Essentials::randomValue()); },
            filename,
            [&] { structure->findValue(Essentials::randomValue()); },
            findFile);
}

template<typename T>
void removeBackFunction(T structure, string filename, ofstream &findFile) {
    testRemoving(
            "\n==============================\n"
            "phase 4. removing elements back \n"
            "==============================\n",
            [&] { structure->addElementFront(Essentials::randomValue()); },
            filename,
            [&] { structure->findValue(Essentials::randomValue()); },
            findFile);
}

template<typename T>
void addMiddleFunction(T structure, string filename, ofstream &findFile) {
    ofstream saveFile;
    saveFile.open(filename);
    cout << "\n==============================\n"
            "phase 5. adding elements middle \n"
            "==============================\n";
    for (int i = startElementQuantity; i <= stopElementQuantity; ++i) {
        addCounter(i);
        saveFile << i << "," << Timer([&] { structure->addElementAnywhere(Essentials::randomValue(), i / 2); })
                 << "\n";
        findFile << i << "," << Timer([&] { structure->findValue(Essentials::randomValue()); }) << "\n";
    }
    saveFile.close();
}

template<typename T>
void removeMiddleFunction(T structure, string filename, ofstream &findFile) {
    ofstream saveFile;
    saveFile.open(filename);
    cout << "\n==============================\n"
            "phase 6. removing elements middle \n"
            "==============================\n ";
    // adding to middle and finding elements
    for (int i = stopElementQuantity; i >= startElementQuantity; --i) {
        removeCounter(i);
        saveFile << i << "," << Timer([&] { structure->removeElementAnywhere(i / 2); }) << "\n";
        findFile << i << "," << Timer([&] { structure->findValue(Essentials::randomValue()); }) << "\n";
    }
    saveFile.close();
}

template<typename T>
void addValueFunction(T structure, string filename, ofstream &findFile) {
    testAdding(
            "\n==============================\n"
            "phase 1. adding elements\n"
            "==============================\n",
            [&] { structure->addValue(Essentials::randomValue()); },
            filename,
            [&] { structure->findValue(Essentials::randomValue()); },
            findFile);
}

template<typename T>
void removeValueFunction(T structure, string filename, ofstream &findFile) {
    testRemoving(
            "\n==============================\n"
            "phase 2. removing elements\n"
            "==============================\n",
            [&] { structure->removeValue(Essentials::randomValue()); },
            filename,
            [&] { structure->findValue(Essentials::randomValue()); },
            findFile);
}

string strResultsArray = "results/array/Array";
string strResultsDoubleList = "results/doubleList/DoubleList";
string strResultsBinaryHeap = "results/binaryHeap/BinaryHeap";
string strResultsRedBlackTree = "results/RBTree/RBTree";
string strResultsAVLTree = "results/AVLTree/AVLTree";

string strAddFront = "AddFront";
string strAddBack = "AddBack";
string strAdd = "AddValue";

string strRemoveFront = "RemoveFront";
string strRemoveBack = "RemoveBack";
string strRemove = "RemoveValue";

string strAddMiddle = "AddMiddle";
string strRemoveMiddle = "RemoveMiddle";

string strFind = "Find";
string txt = ".txt";

string strPhaseCompleted = "\n==============================\n"
                          "Phases Completed! \n"
                          "==============================\n";


void AutomatedTest::array() {
    ofstream FindArrayFile;
    data = Essentials::randomData(startElementQuantity);
    auto *array = new Array(data + 1, data[0]);
    delete[] data;
    FindArrayFile.open(strResultsArray + strFind + txt);
    // adding to front and finding elements
    addFrontFunction(array, strResultsArray + strAddFront + txt, FindArrayFile);

    // removing from front and finding elements
    removeFrontFunction(array, strResultsArray + strRemoveFront + txt, FindArrayFile);

    // adding to back and finding elements
    addBackFunction(array, strResultsArray + strAddBack + txt, FindArrayFile);

    //removing from back and finding elements
    removeBackFunction(array, strResultsArray + strRemoveBack + txt, FindArrayFile);

    // adding to middle and finding elements
    addMiddleFunction(array, strResultsArray + strAddMiddle + txt, FindArrayFile);

    // removing from middle and finding elements
    removeMiddleFunction(array, strResultsArray + strRemoveMiddle + txt, FindArrayFile);

    cout << strPhaseCompleted;
    delete array;
}

void AutomatedTest::doubleList() {
    ofstream FindDoubleListFile;
    data = Essentials::randomData(startElementQuantity);
    auto *array = new DoubleList(data + 1, data[0]);
    delete[] data;
    FindDoubleListFile.open(strResultsDoubleList + strFind + txt);
    // adding to front and finding elements
    addFrontFunction(array, strResultsDoubleList + strAddFront + txt, FindDoubleListFile);

    // removing from front and finding elements
    removeFrontFunction(array, strResultsDoubleList + strRemoveFront + txt, FindDoubleListFile);

    // adding to back and finding elements
    addBackFunction(array, strResultsDoubleList + strAddBack + txt, FindDoubleListFile);

    //removing from back and finding elements
    removeBackFunction(array, strResultsDoubleList + strRemoveBack + txt, FindDoubleListFile);

    // adding to middle and finding elements
    addMiddleFunction(array, strResultsDoubleList + strAddMiddle + txt, FindDoubleListFile);

    // removing from middle and finding elements
    removeMiddleFunction(array, strResultsDoubleList + strRemoveMiddle + txt, FindDoubleListFile);

    cout << strPhaseCompleted;
    delete array;
}


void AutomatedTest::binaryHeap() {
    ofstream FindBinaryHeapFile;
    data = Essentials::randomData(startElementQuantity);
    auto *binaryHeap = new BinaryHeap(data + 1, data[0]);
    delete[] data;
    FindBinaryHeapFile.open(strResultsBinaryHeap + strFind + txt);
    // adding to front and finding elements
    addValueFunction(binaryHeap, strResultsBinaryHeap + strAdd + txt, FindBinaryHeapFile);

    // removing from front and finding elements
    removeValueFunction(binaryHeap, strResultsBinaryHeap + strRemove + txt, FindBinaryHeapFile);

    cout << strPhaseCompleted;
    delete binaryHeap;
}

void AutomatedTest::redBlackTree() {
    ofstream FindRBTreeFile;
    data = Essentials::randomData(startElementQuantity);
    auto *redBlackTree = new RedBlackTree(data + 1, data[0]);
    delete[] data;
    FindRBTreeFile.open(strResultsRedBlackTree + strFind + txt);
    // adding to front and finding elements
    addValueFunction(redBlackTree, strResultsRedBlackTree + strAdd + txt, FindRBTreeFile);

    // removing from front and finding elements
    removeValueFunction(redBlackTree, strResultsRedBlackTree + strRemove + txt, FindRBTreeFile);

    cout << strPhaseCompleted;
    delete redBlackTree;
}

void AutomatedTest::avlTree() {
    ofstream FindAVLTree;
    data = Essentials::randomData(startElementQuantity);
    auto *avltree = new AVLTree(data + 1, data[0]);
    delete[] data;
    FindAVLTree.open(strResultsAVLTree + strFind + txt);
    // adding to front and finding elements
    addValueFunction(avltree, strResultsAVLTree + strAdd + txt, FindAVLTree);

    // removing from front and finding elements
    removeValueFunction(avltree, strResultsAVLTree + strRemove + txt, FindAVLTree);

    cout << strPhaseCompleted;
    delete avltree;
}