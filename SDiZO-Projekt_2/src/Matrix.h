#pragma once

class Matrix {
    int **array;
    int sizeX;
    int sizeY;
public:
    explicit Matrix(int width = 0, int height = 0);

    virtual ~Matrix();

    void addDirectedEdge(int x, int y, int value);

    void display();

    void addUndirectedEdge(int x, int y, int value);

    [[nodiscard]] int get(int x, int y) const;
};