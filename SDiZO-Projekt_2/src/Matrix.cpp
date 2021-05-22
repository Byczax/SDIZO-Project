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

void Matrix::setValue(int x, int y, int value) {
    array[x][y] = value;
}

int Matrix::getValue(int x, int y) {
    return array[x][y];
}

void Matrix::display() {
    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            cout<<"|"<<array[i][j]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"\n";
}