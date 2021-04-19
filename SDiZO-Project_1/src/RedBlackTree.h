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

    void addFixTree(TreeNode *z);

    void rotateLeft(TreeNode *a);

    void rotateRight(TreeNode *a);

    void removeGivenElement(TreeNode *node);

    void removeFixTree(TreeNode *node);

    void printRecursive(const std::string &sp, const std::string &sn, TreeNode *node);

    void removeNodeFromMemory(TreeNode *node);

public:
    RedBlackTree(const int *array = nullptr, int arraySize = 0);

    virtual ~RedBlackTree();

    void addValue(int value);

    bool removeValue(int value);

    bool findValue(int value);

    void display();
};