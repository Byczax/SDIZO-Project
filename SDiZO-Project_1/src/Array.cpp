
#include <iostream>
#include "Array.h"

/**
 * Constructor
 * @param initArray
 * @param mySize
 */
Array::Array(const int *initArray, int mySize) {
    array = new int[mySize];
    size = mySize;
    for (int i = 0; i < mySize; ++i) {
        array[i] = initArray[i];
    }
}

/**
 * Desctructor
 */
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
bool Array::removeElementFront() {
    if (size > 0) {
        --size;
        int *newArray = new int[size];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i + 1];
        }
        delete[] array;
        array = newArray;
        return true;
    }
    return false;
}

/**
 * Remove element in back of the array
 */
bool Array::removeElementBack() {
    if (size > 0) {
        --size;
        int *newArray = new int[size];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        return true;
    }
    return false;
}

/**
 * Remove element anywhere in the array
 * @param index
 */
bool Array::removeElementAnywhere(unsigned int index) {
    if (size > 0 && index < size && index >= 0) {
        --size;
        int *newArray = new int[size];
        unsigned int i;
        for (i = 0; i < index; ++i) {
            newArray[i] = array[i];
        }
        for (i = index; i < size; ++i) {
            newArray[i] = array[i + 1];
        }
        delete[] array;
        array = newArray;
        return true;
    }
    return false;
}

/**
 * Remove value from array if exist
 * @param value
 */
bool Array::removeValue(int value) {
    int index = findValue(value);
    if (index >= 0) {
        removeElementAnywhere(index);
        return true;
    }
    return false;
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

/**
 * Get value from index
 * @param index
 * @return
 */
int Array::getIndexValue(unsigned int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else return false;
}

/**
 * Display all elements in array
 */
void Array::display() {
    std::cout << "\n[";
    if (size > 0) {
        std::cout << array[0];
        for (int i = 1; i < size; ++i) {
            std::cout << ", " << array[i];
        }
    } else {
        std::cout << " ";
    }
    std::cout << "]\n";
}