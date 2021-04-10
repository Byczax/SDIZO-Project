#include "BinaryHeap.h"
#include <iostream>
#include <string>

using namespace std;

BinaryHeap::BinaryHeap(int myHeapSize, const int *initRoot) {
    heapSize = myHeapSize;
    root = new int[myHeapSize];
    for (int i = 0; i < heapSize; ++i) {
        root[i] = initRoot[i];
    }
    if (heapSize > 0) {
        unsigned int i = 1 + (heapSize - 2) / 2;
        do {
            --i;

        } while (i);
    }
}

/**
 * Delete binaryHeap
 */
BinaryHeap::~BinaryHeap() {
    delete[] root;
}

/**
 * Fix binaryHeap down
 * @param index
 */
void BinaryHeap::fixDown(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left <= heapSize && root[left] > root[largest]) {
        largest = left;
    }
    if (right <= heapSize && root[right] > root[largest]) {
        largest = right;
    }
    if (largest != index) {
        int temp = root[index];
        root[index] = root[largest];
        root[largest] = temp;
        fixDown(largest);
    }
}

/**
 * Fix binaryHeap down
 * @param index
 */
void BinaryHeap::fixUp(unsigned int index) {
    if (index) {
        unsigned int smallest = (index - 1) / 2;
        if (root[index] > root[smallest]) {
            int swap = root[smallest];
            root[smallest] = root[index];
            root[index] = swap;
            fixUp(smallest);
        }
    }
}
/**
 * Add element to heap
 * @param value
 */
void BinaryHeap::addElement(int value) {
    int *newRoot = new int[heapSize + 1];
    unsigned int i = 0;
    for (; i < heapSize; ++i) {
        newRoot[i] = root[i];
    }
    newRoot[i] = value;
    delete[] root;
    root = newRoot;
    ++heapSize;
    fixUp(i);
}
/**
 * Remove element from heap
 * @param index
 */
void BinaryHeap::removeElement(unsigned int index) {
    if (index < heapSize && index >= 0) {
        --heapSize;
        int *newArray = new int[heapSize];
        for (unsigned int j = 0; j < index; ++j) {
            newArray[j] = root[j];
        }
        if (heapSize)
            newArray[index] = root[heapSize];
        for (unsigned int j = index + 1; j < heapSize; ++j) {
            newArray[j] = root[j];
        }
        delete[] root;
        root = newArray;
        fixDown(index);
    }
}
/**
 * Remove value from heap
 * @param value
 */
void BinaryHeap::removeValue(int value) {
    removeElement(findValue(value));
}

//TODO find element
int BinaryHeap::findElement(int index) {
    if (index < heapSize){
        return root[index];
    }
    else return false;
}
/**
 * Find if value in heap exit, if so, then return index
 * @param value
 * @return
 */
int BinaryHeap::findValue(int value) {
    for (int i = 0; i < heapSize; ++i) {
        if (root[i] == value) {
            return i;
        }
    }
    return -1;
}
//-----------------Display heap------------------------------------------------
/**
 * display heap, code from https://eduinf.waw.pl/inf/alg/001_search/0112.php
 */
void BinaryHeap::display() {
    printRecursive("", "", 0);
    cout << '\n';
}

/**
 * help function
 * @param sp
 * @param sn
 * @param index
 */
void BinaryHeap::printRecursive(const string &sp, const string &sn, unsigned int index) {
    if (index < heapSize) {
        string cr, cl, cp;
        cr = cl = cp = "  ";
        cr[0] = '*';
        cr[1] = '~';
        cl[0] = '+';
        cl[1] = '-';
        cp[0] = '|';
        string s = sp;
        if (sn == cr) {
            s[s.length() - 2] = ' ';
        }
        printRecursive(s + cp, cr, 2 * index + 2);
        s = s.substr(0, sp.length() - 2);
        cout << s << sn << root[index] << '\n';
        s = sp;
        if (sn == cl) {
            s[s.length() - 2] = ' ';
        }
        printRecursive(s + cp, cl, 2 * index + 1);
    }
}
//-------------------------------------------------------------------------------