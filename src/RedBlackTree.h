#pragma once

#include <iostream>

enum nodeColor {
    RED,
    BLACK
};

class TreeNode {
public:
    int value;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    nodeColor color;

    TreeNode(int val, TreeNode *p, TreeNode *l, TreeNode *r, nodeColor givenColor = RED);
};

class RedBlackTree {

    TreeNode *nil;
    TreeNode *root;

public:
    RedBlackTree(const int *array, int arraySize);

    virtual ~RedBlackTree();

    void addElement(int value);

    void addFixTree(TreeNode *z);

    void rotateLeft(TreeNode *a);

    void rotateRight(TreeNode *a);

    bool removeValue(int value);

    void removeGivenElement(TreeNode *node);

    void removeFixTree(TreeNode *node);

    void printRecursive(const std::string &sp, const std::string &sn, TreeNode *node);

    bool findGivenNumber(int number);

    void display();

    void removeNodeFromMemory(TreeNode *node);
};