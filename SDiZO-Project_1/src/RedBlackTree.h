#pragma once

#include <iostream>

enum nodeColor {
    RED,
    BLACK
};

class TreeNode {
public:
    int value;// node value
    TreeNode *parent;// node parent pointer
    TreeNode *left;// node left node pointer
    TreeNode *right;// node right node pointer
    nodeColor color;// node color

    // Constructor
    TreeNode(int val, TreeNode *p, TreeNode *l, TreeNode *r, nodeColor givenColor = RED);
};

class RedBlackTree {

    TreeNode *nil;// null leaf
    TreeNode *root;// root

    // Fix tree after adding element
    void addFixTree(TreeNode *z);

    // Rotate tree left
    void rotateLeft(TreeNode *a);

    // Rotate tree right
    void rotateRight(TreeNode *a);

    // Remove given node from the tree
    void removeGivenElement(TreeNode *node);

    // fix tree after removing element
    void removeFixTree(TreeNode *node);

    // display
    void printRecursive(const std::string &sp, const std::string &sn, TreeNode *node);

    // delete given node
    void removeNodeFromMemory(TreeNode *node);

public:
    // Constructor
    RedBlackTree(const int *array = nullptr, int arraySize = 0);

    // Deconstructor
    virtual ~RedBlackTree();

    // Add value to the tree
    void addValue(int value);

    // Remove value from the tree
    bool removeValue(int value);

    // Find value in the tree
    bool findValue(int value);

    // Display
    void display();
};