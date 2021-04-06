#pragma once

#include <iostream>

enum nodeColour {
    RED,
    BLACK
};

class TreeNode {
public:
    int value;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    nodeColour color;

    TreeNode(int val, TreeNode *p, TreeNode *l, TreeNode *r, nodeColour givenColor = RED);
};

class RedBlackTree {


public:
    RedBlackTree(const int *array, int arraySize);

    virtual ~RedBlackTree();

    void addElement(int number);

    void addFixTree(TreeNode *z);

    void rotateLeft(TreeNode *a);

    void rotateRight(TreeNode *a);
};