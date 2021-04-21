#include "BinaryHeap.h"
#include <iostream>

using std::string;

/**
 * Concstructor
 * @param initRoot
 * @param myHeapSize
 */
BinaryHeap::BinaryHeap(const int *initRoot, int myHeapSize) {
    size = myHeapSize;
    heap = new int[size];
    for (int i = 0; i < myHeapSize; ++i) {
        heap[i] = initRoot[i];
    }
    if (size != 0) {
        unsigned int i = 1 + (size - 2) / 2;
        do {
            --i;
            heapifyDown(i);
        } while (i);
    }
}

/**
 * Deconstructor
 */
BinaryHeap::~BinaryHeap() {
    delete[] heap;
}

/**
 * Get node parent
 * @param index
 * @return
 */
int BinaryHeap::getParent(int index) {
    return (index - 1) / 2;
}

/**
 * Get node left child
 * @param index
 * @return
 */
int BinaryHeap::getLeftChild(int index) {
    return (2 * index + 1);
}

/**
 * Get node right child
 * @param index
 * @return
 */
int BinaryHeap::getRightChild(int index) {
    return (2 * index + 2);
}

/**
 * Change size of the heap
 * @param newSize
 */
void BinaryHeap::relocate(int newSize) {
    int *temp = new int[newSize];
    if (newSize >= size) {
        for (int i = 0; i < size; i++) {
            temp[i] = heap[i];
        }
    } else {
        for (int i = 0; i < newSize; i++) {
            temp[i] = heap[i];
        }
    }
    delete[] heap;
    heap = temp;
}

/**
 * Swap elements
 * @param x
 * @param y
 */
void BinaryHeap::swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * Add element to heap
 * @param value
 */
void BinaryHeap::addValue(int value) {
    relocate(size + 1);
    ++size;
    int i = size - 1;
    heap[i] = value;
    heapifyUp(i);
}

/**
 * Remove element from heap
 * @return
 */
void BinaryHeap::removeIndex(int index) {
    if (index >= 0 && index < size) {
        --size;
        int *newArray = new int[size];
        for (unsigned int j = 0; j < index; ++j) {
            newArray[j] = heap[j];
        }
        if (size > 0) {
            newArray[index] = heap[size];
        }
        for (unsigned int j = index + 1; j < size; ++j) {
            newArray[j] = heap[j];
        }
        delete[] heap;
        heap = newArray;
        heapifyDown(index);
    }
}

/**
 * Remove value from heap
 * @param value
 */
void BinaryHeap::removeValue(int number) {
    removeIndex(findValue(number));
}

/**
 * Delete given value from the heap
 * @param value
 */
void BinaryHeap::deleteValue(int value) {
    int index = findValue(value);
    if (index < 0)
        return;

    int oldValue = heap[index];
    int newValue = heap[size - 1];

    heap[index] = newValue;
    relocate(size - 1);

    if (newValue > oldValue) {
        heapifyUp(index);
    } else if (newValue < oldValue) {
        heapifyDown(index);
    }
    --size;
}

/**
 * Fix heap up
 * @param index
 */
void BinaryHeap::heapifyUp(int index) {
    int parentIndex = getParent(index);
    while (index > 0 && heap[parentIndex] < heap[index]) {
        swap(&heap[parentIndex], &heap[index]);
        index = parentIndex;
        parentIndex = getParent(index);
    }
}

/**
 * Fix heap down
 * @param index
 */
void BinaryHeap::heapifyDown(int index) {
    int leftChild = getLeftChild(index);
    int rightChild = getRightChild(index);
    int biggest = index;

    if (leftChild < size && heap[leftChild] > heap[biggest])
        biggest = leftChild;
    if (rightChild < size && heap[rightChild] > heap[biggest])
        biggest = rightChild;
    if (biggest != index) {
        swap(&heap[index], &heap[biggest]);
        heapifyDown(biggest);
    }
}

/**
 * Find value in heap
 * @param value
 * @return
 */
int BinaryHeap::findValue(int value) {
    for (int i = 0; i < size; i++) {
        if (heap[i] == value)
            return i;
    }
    return -1;
}
//-----------------Display heap------------------------------------------------

/**
 * display heap, code from https://eduinf.waw.pl/inf/alg/001_search/0112.php
 */
void BinaryHeap::display() {
    std::cout << '\n';
    printRecursive("", "", 0);
    std::cout << '\n';
}

/**
 * help function
 * @param sp
 * @param sn
 * @param index
 */
void BinaryHeap::printRecursive(const string &sp, const string &sn, unsigned int index) {
    if (index < size) {
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
        std::cout << s << sn << heap[index] << '\n';
        s = sp;
        if (sn == cl) {
            s[s.length() - 2] = ' ';
        }
        printRecursive(s + cp, cl, 2 * index + 1);
    }
}
//-------------------------------------------------------------------------------