#include <iostream>
#include "array.h"


Array::Array(const int *initArray, int mySize) {
    array = new int[mySize];
    size = mySize;
    for (int i = 0; i < mySize; ++i) {
        array[i] = initArray[i];
    }
}

Array::~Array() {
    delete[] array;
}

/**
 * add new element on front in array
 * @param value
 */
void Array::addElementFront(int value) {
    ++size;
    int *newArray = new int[size];
    newArray[0] = value;
    for (unsigned int i = 1; i < size; ++i) {
        newArray[i] = array[i - 1];
    }
    delete[] array;
    array = newArray;
}

void Array::addElementBack(int value) {
    int *newArray = new int[size + 1];
    for (unsigned int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }
    newArray[size] = value;
    ++size;
    delete[] array;
    array = newArray;
}

void Array::addElementAnywhere(int value, unsigned int index) {
    if (index <= size) {
        ++size;
        int *newArray = new int[size];
        unsigned int i = 0;
        for (; i < index; ++i) {
            newArray[i] = array[i];
        }
        newArray[i] = value;
        ++i;
        for (; i < size; ++i) {
            newArray[i] = array[i - 1];
        }
        delete[] array;
        array = newArray;
    }
}

void Array::removeElementFront() {
    if (size > 0) {
        --size;
        int *newArray = new int[size];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i + 1];
        }
        delete array;
        array = newArray;
    }
}

void Array::removeElementBack() {
    if (size > 0) {
        --size;
        int *newArray = new int[size];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete array;
        array = newArray;
    }
}

void Array::removeElementAnywhere(unsigned int index) {
    if (size > 0 && index <= size && index > 0) {
        --size;
        int *newArray = new int[size];
        unsigned int i = 0;
        for (i = 0; i < index; ++i) {
            newArray[i] = array[i];
        }
        for (; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete array;
        array = newArray;
    }
}

void Array::removeValue(int value) {
    removeElementAnywhere(findValue(value));
}

int Array::findValue(int value) {
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            if (array[i] == value) {
                return i;
            }
        }
    }
    return -1;
}

void Array::display() {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i];
    }
}