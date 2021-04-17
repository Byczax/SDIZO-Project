#include "BinaryHeap.h"

using std::string;

/**
 * Concstructor
 * @param initRoot
 * @param myHeapSize
 */
BinaryHeap::BinaryHeap(const int *initRoot, int myHeapSize) {
    size = myHeapSize;
    heap = new int[size];
    for (int i = 0; i < myHeapSize; ++i) {
        heap[i] = initRoot[i];
    }
    if (size != 0) {
        unsigned int i = 1 + (size - 2) / 2;
        do {
            --i;
            heapify(i);
        } while (i);
    }
}

/**
 * Deconstructor
 */
BinaryHeap::~BinaryHeap() {
    delete[] heap;
}

int BinaryHeap::getParent(int index) {
    return (index - 1) / 2;
}

int BinaryHeap::getLeftChild(int index) {
    return (2 * index + 1);
}

int BinaryHeap::getRightChild(int index) {
    return (2 * index + 2);
}

void BinaryHeap::relocate(int newSize) {
    int *temp = new int[newSize];
    if (newSize >= size) {
        for (int i = 0; i < size; i++) {
            temp[i] = heap[i];
        }
    } else {
        for (int i = 0; i < newSize; i++) {
            temp[i] = heap[i];
        }
    }
    delete[] heap;
    heap = temp;
}
/**
 * Swap elements
 * @param x
 * @param y
 */
void BinaryHeap::swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
/**
 * Add element to heap
 * @param key
 */
void BinaryHeap::addValue(int key) {
    relocate(size + 1);
    size++;
    int i = size - 1;
    heap[i] = key;

    while (i != 0 && heap[getParent(i)] < heap[i]) {
        swap(&heap[i], &heap[getParent(i)]);
        i = getParent(i);
    }
}

void BinaryHeap::increaseKey(int index) {
    heap[index] = INT_MAX;
    while (index != 0 && heap[getParent(index)] < heap[index]) {
        swap(&heap[index], &heap[getParent(index)]);
        index = getParent(index);
    }
}
/**
 * Remove element from heap
 * @return
 */
int BinaryHeap::removeIndex() {
    if (size <= 0) {
        return 0;
    } else if (size == 1) {
        size--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[size - 1];
    relocate(size - 1);
    size--;
    heapify(0);

    return root;
}
/**
 * Remove value from heap
 * @param value
 */
void BinaryHeap::removeValue(int value) {
    int key = findValue(value);
    if (key == -1) {
        std::cout << "Could not remove value: " << value << "\n";
        return;
    }
    increaseKey(key);
    removeIndex();
}

/**
 * Fix heap
 * @param index
 */
void BinaryHeap::heapify(int index) {
    int leftChild = getLeftChild(index);
    int rightChild = getRightChild(index);
    int biggest = index;

    if (leftChild < size && heap[leftChild] > heap[biggest])
        biggest = leftChild;
    if (rightChild < size && heap[rightChild] > heap[biggest])
        biggest = rightChild;
    if (biggest != index) {
        swap(&heap[index], &heap[biggest]);
        heapify(biggest);
    }
}

/**
 * Find value in heap
 * @param value
 * @return
 */
int BinaryHeap::findValue(int value) {
    for (int i = 0; i < size; i++) {
        if (heap[i] == value)
            return i;
    }
    return -1;
}
//-----------------Display heap------------------------------------------------

/**
 * display heap, code from https://eduinf.waw.pl/inf/alg/001_search/0112.php
 */
void BinaryHeap::display() {
    printRecursive("", "", 0);
    std::cout << '\n';
}

/**
 * help function
 * @param sp
 * @param sn
 * @param index
 */
void BinaryHeap::printRecursive(const string &sp, const string &sn, unsigned int index) {
    if (index < size) {
        string cr, cl, cp;
        cr = cl = cp = "  ";
        cr[0] = '*';
        cr[1] = '~';
        cl[0] = '+';
        cl[1] = '-';
        cp[0] = '|';
        string s = sp;
        if (sn == cr) {
            s[s.length() - 2] = ' ';
        }
        printRecursive(s + cp, cr, 2 * index + 2);
        s = s.substr(0, sp.length() - 2);
        std::cout << s << sn << heap[index] << '\n';
        s = sp;
        if (sn == cl) {
            s[s.length() - 2] = ' ';
        }
        printRecursive(s + cp, cl, 2 * index + 1);
    }
}
//-------------------------------------------------------------------------------