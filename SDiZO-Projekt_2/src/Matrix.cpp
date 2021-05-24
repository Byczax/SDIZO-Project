#include <iostream>
#include "Matrix.h"

using std::cout;

Matrix::Matrix(int width, int height) {
    sizeX = width;
    sizeY = height;
    array = new int *[sizeX];
    for (int i = 0; i < sizeX; ++i) {
        array[i] = new int[sizeY];
        for (int j = 0; j < sizeY; ++j) {
            array[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < sizeX; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

int Matrix::get(int x, int y) const {
    return array[x][y];
}


void Matrix::addDirectedEdge(int x, int y, int value) {
    array[x][y] = value;
}

void Matrix::addUndirectedEdge(int x, int y, int value) {
    array[x][y] = value;
    array[y][x] = value;

}

void Matrix::display() {
    cout << "\nx\\y | ";
    for (int i = 0; i < sizeY; ++i) {
        if (i < 10) {
            cout << " " << i << "  | ";
        } else if (i < 100) {
            cout << i << "  | ";
        } else {
            cout << i << " | ";
        }
    }
    cout << "\n---  ";
    for (int i = 0; i < sizeY; ++i) {
        cout << "----- ";
    }
    cout << "\n";
    for (int i = 0; i < sizeY; ++i) {
        if (i < 10) {
            cout << " " << i << "  | ";
        } else if (i < 100) {
            cout << i << "  | ";
        } else {
            cout << i << " | ";
        }
        for (int j = 0; j < sizeX; ++j) {
            if (array[i][j] < 10) {
                cout << " " << array[i][j] << "  | ";
            } else if (array[i][j] < 100) {
                cout << array[i][j] << "  | ";
            } else {
                cout << array[i][j] << " | ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}