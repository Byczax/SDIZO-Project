#pragma once

#include <string>

class AVLTree {
    class AVLTreeNode {
    public:
        int data;
        AVLTreeNode *left;
        AVLTreeNode *right;
        int balance;

        AVLTreeNode();

        AVLTreeNode(int);

        ~AVLTreeNode();

        void display(int = 0);
    };

    AVLTreeNode *root;
    AVLTreeNode *nil;

    void preorderBST(AVLTreeNode *);

    void inorderBST(AVLTreeNode *);

    void postorderBST(AVLTreeNode *);

    void deleteNode(AVLTreeNode *&);

    void rotateRight(AVLTreeNode *&);

    void rotateLeft(AVLTreeNode *&);

    bool incrementBalance(AVLTreeNode *&);

    bool decrementBalance(AVLTreeNode *&);

    bool insertValue(int, AVLTreeNode *&);

    bool removeValue(int, AVLTreeNode *&);

    int getMin(AVLTreeNode *);

public:
    AVLTree(const int *array, int arraySize);

    ~AVLTree();

    void addValue(int);

    void removeValue(int);

    AVLTreeNode *findValue(int);

    void preorder();

    void inorder();

    void postorder();

    void display();

    void printRecursive(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &sp,
                        const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &sn,
                        AVLTreeNode *node);

    void display2();
};