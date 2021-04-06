#pragma once


#include <string>

class BinaryHeap {
    int heapSize;
    int *root;
public:
    BinaryHeap(int heapSize, const int *root);

    virtual ~BinaryHeap();

    void fixDown(int index);

    void fixUp(unsigned int index);

    void addElement(int value);

    void removeElement(unsigned int index);

    void removeValue(int value);

    void findElement(int value);

    void display();

    int findValue(int value);

    void printRecursive(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &sp,
                        const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &sn,
                        unsigned int index);
};