#pragma once

class Array {
    int *array; // pointer on first element
    int size; // array length

public:
    // constructor with default values
    explicit Array(const int *initArray = nullptr, int size = 0);

    // destructor
    virtual ~Array();

    // add new element to the front of the array
    void addElementFront(int value);

    // add new element to the back of the array
    void addElementBack(int value);

    // add new element on given index position in the array
    void addElementAnywhere(int value, unsigned int index);

    // remove element from the front of the array
    void removeElementFront();

    // remove element from the back of the array
    void removeElementBack();

    // remove element from given index
    void removeElementAnywhere(unsigned int index);

    // remove given value
    void removeValue(int value);

    // find given value
    int findValue(int value);

    // get value under the index
    int getIndexValue(unsigned int index);

    // display array
    void display();
};