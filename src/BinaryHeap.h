#pragma once

#include <string>

using namespace std;

class BinaryHeap {
    int heapSize;
    int *root;

    void fixDown(int index);

    void fixUp(unsigned int index);

    void printRecursive(const string &sp, const string &sn, unsigned int index);

public:
    BinaryHeap(const int *root, int heapSize);

    virtual ~BinaryHeap();

    void addElement(int value);

    void removeElement(unsigned int index);

    void removeValue(int value);

    int findElement(int value);

    void display();

    int findValue(int value);
};