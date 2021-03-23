#include "array.h"

class Array {
    int *array; // pointer on first element
    int size; // array length

public:
    /**
     * Creating new Array
     * @param givenArray
     * @param size
     */
    Array(int *givenArray, int givenSize) : array(givenArray), size(givenSize) {
        array = new int[givenSize];
        size = givenSize;
        for (int i = 0; i < size; ++i) {
            array[i] = givenArray[i];
        }
    }
    /**
     * destructor
     */
    virtual ~Array() {
        delete[] array;
    }

public:
    /**
     * add new element on front in array
     * @param value
     */
    void addElementFront(int value) {
        ++size;
        int *newArray = new int[size];
        newArray[0] = value;
        for (unsigned int i = 1; i < size; ++i) {
            newArray[i] = array[i - 1];
        }
        delete[] array;
        array = newArray;
    }

    void addElementBack(int value) {
        int *newArray = new int[size + 1];
        for (unsigned int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        newArray[size] = value;
        ++size;
        delete[] array;
        array = newArray;
    }

    void addElementAnywhere(int value, unsigned int index) {
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
};