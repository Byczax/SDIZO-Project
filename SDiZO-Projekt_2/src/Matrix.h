#pragma once

class Matrix {

    int **array;
    int sizeX;
    int sizeY;
public:
    Matrix(int width, int height);

    virtual ~Matrix();

    void setValue(int x, int y, int value);

    int getValue(int x, int y);

    void display();
};
