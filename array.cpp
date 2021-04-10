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
 * addElement new element on front in array
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

/**
 * Add element in back of the array
 * @param value
 */
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

/**
 * Add element anywhere in the array
 * @param value
 * @param index
 */
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

/**
 * Remove element in front of the array
 */
void Array::removeElementFront() {
    if (size > 0) {
        --size;
        int *newArray = new int[size];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i + 1];
        }
        delete[] array;
        array = newArray;
    }
}

/**
 * Remove element in back of the array
 */
void Array::removeElementBack() {
    if (size > 0) {
        --size;
        int *newArray = new int[size];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
}

/**
 * Remove element anywhere in the array
 * @param index
 */
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
        delete[] array;
        array = newArray;
    }
}

/**
 * Remove value from array if exist
 * @param value
 */
void Array::removeValue(int value) {
    removeElementAnywhere(findValue(value));
}

/**
 * find element in array
 * @param value
 * @return
 */
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

int Array::getIndexValue(unsigned int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else throw std::invalid_argument("Niepoprawny indeks");
}

/**
 * Display all elements in array
 */
void Array::display() {
    for (int i = 0; i < size; ++i) {
        std::cout << i << ". " << array[i] << "\n";
    }
}


