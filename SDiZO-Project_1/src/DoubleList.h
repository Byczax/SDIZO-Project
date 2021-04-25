#pragma once

class ListNode {
public:
    int value;// element value
    ListNode *prev;// pointer to previous element
    ListNode *next;// pointer to next element
};

class DoubleList {
    ListNode *head = nullptr;// first element
    ListNode *tail = nullptr;// last element
    int size = 0;// list size

public:
    // Constructor
    DoubleList(int *array = nullptr, int arraySize = 0);

    // Deconstructor
    virtual ~DoubleList();

    // Add element to the front of the list
    void addElementFront(int value);

    // Add element to the back of the list
    void addElementBack(int value);

    // Add element anywhere in the list
    void addElementAnywhere(int value, unsigned int index);

    // Remove element from the front in the list
    bool removeElementFront();

    // remove element from the back of the list
    bool removeElementBack();

    // remove element from anywhere in the list
    bool removeElementAnywhere(unsigned int index);

    // remove given value from the list
    bool removeValue(int value);

    // find value in the list
    int findValue(int value);

    // display
    void display();
};