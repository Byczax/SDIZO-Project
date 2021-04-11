#pragma once

class ListNode {
public:
    int value;
    ListNode *prev;
    ListNode *next;
};

class DoubleList {
    ListNode *first_element = nullptr;
    int size = 0;
public:
    DoubleList(int *array, int arraySize);

    void addElementFront(int value);

    void addElementBack(int value);

    void addElementAnywhere(int value, unsigned int index);

    void removeElementFront();

    void removeElementBack();

    void removeElementAnywhere(unsigned int index);

    void removeValue(int value);

    ListNode *findValue(int value);

    void display();

    virtual ~DoubleList();
};