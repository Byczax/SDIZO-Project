#pragma once

#include <iostream>
#include <iomanip>

class BinaryHeap {
    int *heap;
    int capacity;
    int size;

    int getParent(int);

    int getLeftChild(int);

    int getRightChild(int);

    void relocate(int);

    void swap(int *, int *);

    void heapify(int);

    void increaseKey(int);

    void printRecursive(const std::string &sp, const std::string &sn, unsigned int index);

    int removeIndex();

public:
    BinaryHeap(const int *initRoot = nullptr, int myHeapSize = 0);

    ~BinaryHeap();

    void addValue(int);

    void removeValue(int);

    int findValue(int);

    void display();
};