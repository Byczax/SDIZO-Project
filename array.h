#pragma once

class Array {
    int *array; // pointer on first element
    int size; // array length
public:
    Array(const int *initArray, int size);

    virtual ~Array();

public:
    void addElementFront(int value);

    void addElementBack(int value);

    void addElementAnywhere(int value, unsigned int index);

    void removeElementFront();

    void removeElementBack();

    void removeElementAnywhere(unsigned int index);

    void removeValue(int value);

    int findValue(int value);

    void display();
};