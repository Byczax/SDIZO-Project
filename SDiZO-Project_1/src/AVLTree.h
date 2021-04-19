#pragma once

#include <string>

class AVLTree {
    class AVLTreeNode {
    public:
        int value;
        AVLTreeNode *left;
        AVLTreeNode *right;
        int balance;

        AVLTreeNode();

        AVLTreeNode(int value);

        ~AVLTreeNode();
    };

    AVLTreeNode *root;
    AVLTreeNode *nil;

    void deleteNode(AVLTreeNode *&);

    void rotateRight(AVLTreeNode *&);

    void rotateLeft(AVLTreeNode *&);

    bool incrementBalance(AVLTreeNode *&);

    bool decrementBalance(AVLTreeNode *&);

    bool insertValue(int, AVLTreeNode *&);

    bool removeValue(int, AVLTreeNode *&);

    int getMin(AVLTreeNode *);

    void printRecursive(const std::string &sp, const std::string &sn, AVLTreeNode *node);

public:
    AVLTree(const int *array = nullptr, int arraySize = 0);

    ~AVLTree();

    void addValue(int);

    void removeValue(int);

    AVLTreeNode *findValue(int);

    void display();
};