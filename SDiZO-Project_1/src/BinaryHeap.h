#pragma once

#include <string>

class BinaryHeap {
    int *heap;// pointer to heap
    int size;// heap size

    //get parent for given index
    int getParent(int index);

    // get left child for given index element
    int getLeftChild(int index);

    // get right child for given index element
    int getRightChild(int index);

    // change heap size
    void relocate(int index);

    // swap two elements
    void swap(int *a, int *b);

    // fix heap down
    void heapifyDown(int index);

    // fix heap up
    void heapifyUp(int index);

    // display
    void printRecursive(const std::string &sp, const std::string &sn, unsigned int index);

    // remove value under the index
    void removeIndex(int index);

public:
    // constructor
    BinaryHeap(const int *initRoot = nullptr, int myHeapSize = 0);

    // deconstructor
    ~BinaryHeap();

    // add value to heap
    void addValue(int value);

    // remove value from heap
    void removeValue(int value);

    // find value in the heap
    int findValue(int value);

    // display
    void display();

    // delete value from the heap
    void deleteValue(int value);
};