#pragma once

#include <string>

class AVLTree {
    class AVLTreeNode {
    public:
        int value;// node value
        AVLTreeNode *left;// pointer to left node
        AVLTreeNode *right;// pointer to right node
        int balance;// node balance
        // empty node constructor
        AVLTreeNode();

        // node constructor with value
        AVLTreeNode(int value);

        // destructor
        ~AVLTreeNode();
    };

    AVLTreeNode *root;// root
    AVLTreeNode *nil;// null leaf
    // Delete given node
    void deleteNode(AVLTreeNode *&);

    // Rotate right
    void rotateRight(AVLTreeNode *&);

    // Rotate left
    void rotateLeft(AVLTreeNode *&);

    // Increment balance and fix iff needed
    bool incrementBalance(AVLTreeNode *&);

    // Decrement balance and fix if needed
    bool decrementBalance(AVLTreeNode *&);

    // Insert given value
    bool insertValue(int, AVLTreeNode *&);

    // Remove given value
    bool removeValue(int, AVLTreeNode *&);

    // Get minimal value from the tree
    int getMin(AVLTreeNode *);

    // display
    void printRecursive(const std::string &sp, const std::string &sn, AVLTreeNode *node);

public:
    // Constructor
    AVLTree(const int *array = nullptr, int arraySize = 0);

    // Destructor
    ~AVLTree();

    // Add value to the tree
    void addValue(int);

    // Remove value from the tree
    void removeValue(int);

    // Find value in the tree
    AVLTreeNode *findValue(int);

    // Display
    void display();
};