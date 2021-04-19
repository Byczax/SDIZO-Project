#pragma once

#include <string>

class BinaryHeap {
    int *heap;
    int size;

    int getParent(int);

    int getLeftChild(int);

    int getRightChild(int);

    void relocate(int);

    void swap(int *, int *);

    void heapifyDown(int);

    void printRecursive(const std::string &sp, const std::string &sn, unsigned int index);

    void removeIndex(unsigned int index);

public:
    BinaryHeap(const int *initRoot = nullptr, int myHeapSize = 0);

    ~BinaryHeap();

    void addValue(int);

    bool removeValue(int);

    int findValue(int);

    void display();
};