#include "BinaryHeap.h"

using std::string;

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
 * Delete binaryHeap
 */
BinaryHeap::~BinaryHeap() {
    delete[] heap;
    size = 0;
}

size_t BinaryHeap::getParent(size_t index) {
    return (index - 1) / 2;
}

size_t BinaryHeap::getLeftChild(size_t index) {
    return (2 * index + 1);
}

size_t BinaryHeap::getRightChild(size_t index) {
    return (2 * index + 2);
}

void BinaryHeap::relocate(size_t newSize) {
    int *temp = new int[newSize];
    if (newSize >= size) {
        for (size_t i = 0; i < size; i++) {
            temp[i] = heap[i];
        }
    } else {
        for (size_t i = 0; i < newSize; i++) {
            temp[i] = heap[i];
        }
    }
    delete heap;
    heap = temp;
}

void BinaryHeap::swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void BinaryHeap::push(int key) {
    relocate(size + 1);
    size++;
    int i = size - 1;
    heap[i] = key;

    while (i != 0 && heap[getParent(i)] < heap[i]) {
        swap(&heap[i], &heap[getParent(i)]);
        i = getParent(i);
    }
}

void BinaryHeap::increaseKey(size_t index, int newValue) {
    heap[index] = newValue;
    while (index != 0 && heap[getParent(index)] < heap[index]) {
        swap(&heap[index], &heap[getParent(index)]);
        index = getParent(index);
    }
}

int BinaryHeap::pop() {
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

void BinaryHeap::remove(int value) {
    size_t key = find(value);
    if (key == -1) {
        std::cout << "Could not remove value: " << value << std::endl;
        return;
    }

    increaseKey(key, INT_MAX);
    pop();
}

void BinaryHeap::heapify(size_t index) {
    size_t leftChild = getLeftChild(index);
    size_t rightChild = getRightChild(index);
    size_t biggest = index;

    if (leftChild < size && heap[leftChild] > heap[biggest])
        biggest = leftChild;
    if (rightChild < size && heap[rightChild] > heap[biggest])
        biggest = rightChild;
    if (biggest != index) {
        swap(&heap[index], &heap[biggest]);
        heapify(biggest);
    }
}

size_t BinaryHeap::find(int value) {
    for (size_t i = 0; i < size; i++) {
        if (heap[i] == value)
            return i;
    }

    return -1;
}

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