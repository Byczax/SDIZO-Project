#pragma once

class Matrix {
    int **array;
    int sizeX;
    int sizeY;
public:
    // constructor
    explicit Matrix(int width = 0, int height = 0);

    // destructor
    virtual ~Matrix();

    // used when directed = true
    void addDirectedEdge(int x, int y, int value);

    // display matrix
    void display();

    // used when directed = false
    void addUndirectedEdge(int x, int y, int value);

    [[nodiscard]] int get(int x, int y) const;
};