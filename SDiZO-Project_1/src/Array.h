#pragma once

class Array {
    int *array; // pointer on first element
    int size; // array length


public:
    explicit Array(const int *initArray = nullptr, int size = 0);

    virtual ~Array();

    void addElementFront(int value);

    void addElementBack(int value);

    void addElementAnywhere(int value, unsigned int index);

    void removeElementFront();

    void removeElementBack();

    void removeElementAnywhere(unsigned int index);

    void removeValue(int value);

    int findValue(int value);

    int getIndexValue(unsigned int index);

    void display();
};