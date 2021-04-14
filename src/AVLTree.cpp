#include "AVLTree.h"
#include <iostream>
#include <iomanip>

using namespace std;

AVLTree::AVLTreeNode::AVLTreeNode() {
}

AVLTree::AVLTreeNode::AVLTreeNode(int _data) {
    data = _data;
    left = right = nullptr;
    balance = 0;
}

AVLTree::AVLTreeNode::~AVLTreeNode() {
    data = 0;
    left = right = nullptr;
    balance = 0;
}

void AVLTree::AVLTreeNode::display(int offset) {
    bool isNil = false;

    if (this == this->left && this->left == this->right)
        isNil = true;

    if (isNil)
        return;

    if (right) right->display(5 + offset);
    std::cout << std::setw(offset) << data << "(" << balance << ")" << std::endl;
    if (left) left->display(5 + offset);
}

AVLTree::AVLTree(const int *array, int arraySize) {
    nil = new AVLTreeNode();
    nil->left = nil;
    nil->right = nil;
    nil->balance = 0;
    root = nil;
    for (int i = 0; i < arraySize; ++i) {
        this->addValue(array[i]);
    }
}

AVLTree::~AVLTree() {
    deleteNode(root);
    root = nullptr;
    delete nil;
    nil = nullptr;
}

void AVLTree::addValue(int data) {
    insertValue(data, root);
}

void AVLTree::removeValue(int data) {
    removeValue(data, root);
}

void AVLTree::deleteNode(AVLTreeNode *&node) {
    if (node == nil)
        return;

    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}

void AVLTree::rotateRight(AVLTreeNode *&node) {
    AVLTreeNode *x = node;
    AVLTreeNode *y = node->left;

    x->left = y->right;
    y->right = x;
    node = y;

    x->balance += 1;
    if (y->balance < 0) x->balance += -y->balance;

    y->balance += 1;
    if (x->balance > 0) y->balance += x->balance;
}

void AVLTree::rotateLeft(AVLTreeNode *&node) {
    AVLTreeNode *x = node;
    AVLTreeNode *y = node->right;

    x->right = y->left;
    y->left = x;
    node = y;

    x->balance -= 1;
    if (y->balance > 0) x->balance -= y->balance;

    y->balance -= 1;
    if (x->balance < 0) y->balance -= -x->balance;
}

bool AVLTree::incrementBalance(AVLTreeNode *&node) {
    node->balance++;

    if (node->balance == 0)
        return false;

    if (node->balance == 1)
        return true;

    if (node->balance == 2) {
        if (node->right->balance == -1)
            rotateRight(node->right);

        rotateLeft(node);

        return false;
    }

    return true;
}

bool AVLTree::decrementBalance(AVLTreeNode *&node) {
    node->balance--;

    if (node->balance == 0)
        return false;

    if (node->balance == -1)
        return true;

    if (node->balance == -2) {
        if (node->left->balance == 1)
            rotateLeft(node->left);

        rotateRight(node);

        return false;
    }

    return true;
}

bool AVLTree::insertValue(int data, AVLTreeNode *&node) {
    if (node == nil) {
        node = new AVLTreeNode(data);
        node->left = nil;
        node->right = nil;
        return true;
    } else if (data > node->data) {
        return insertValue(data, node->right) && incrementBalance(node);
    } else if (data < node->data) {
        return insertValue(data, node->left) && decrementBalance(node);
    }

    return false;
}

int AVLTree::getMin(AVLTreeNode *node) {
    AVLTreeNode *temp = node;

    while (temp->left != nil)
        temp = temp->left;

    return temp->data;
}

bool AVLTree::removeValue(int data, AVLTreeNode *&node) {
    if (node == nil)
        return false;
    else if (node->data < data)
        return removeValue(data, node->right) && !decrementBalance(node);
    else if (node->data > data)
        return removeValue(data, node->left) && !incrementBalance(node);
    else {
        if (node->left == nil && node->right == nil) {
            AVLTreeNode *nodeToRemove = node;
            node = nil;
            deleteNode(nodeToRemove);
        } else if (node->left != nil && node->right != nil) {
            AVLTreeNode *currentNode = node;
            int minNodeValue = getMin(node->right);

            bool isHeightChanged = removeValue(minNodeValue, node);
            currentNode->data = minNodeValue;

            return isHeightChanged;
        } else {
            AVLTreeNode *nodeToRemove = node;

            if (node->left == nil) {
                node = nodeToRemove->right;
                nodeToRemove->right = nil;
            } else {
                node = nodeToRemove->left;
                nodeToRemove->left = nil;
            }

            deleteNode(nodeToRemove);
        }

        return true;
    }
}

AVLTree::AVLTreeNode *AVLTree::findValue(int data) {
    AVLTreeNode *node = root;

    while (node != nil) {
        if (node->data > data) {
            node = node->left;
        } else if (node->data < data) {
            node = node->right;
        } else {
            return node;
        }
    }

    return nullptr;
}

void AVLTree::preorder() {
    preorderBST(root);
}

void AVLTree::preorderBST(AVLTreeNode *node) {
    if (node == nil)
        return;

    std::cout << node->data << std::endl;
    preorderBST(node->left);
    preorderBST(node->right);
}

void AVLTree::inorder() {
    inorderBST(root);
}

void AVLTree::inorderBST(AVLTreeNode *node) {
    if (node == nil)
        return;

    inorderBST(node->left);
    std::cout << node->data << std::endl;
    inorderBST(node->right);
}

void AVLTree::postorder() {
    postorderBST(root);
}

void AVLTree::postorderBST(AVLTreeNode *node) {
    if (node == nil)
        return;

    postorderBST(node->left);
    postorderBST(node->right);
    std::cout << node->data << std::endl;
}

void AVLTree::display() {
    if (root != nil)
        root->display();
}

void AVLTree::display2() {
    printRecursive("", "", root);
    cout << '\n';
}

void AVLTree::printRecursive(const string &sp, const string &sn, AVLTreeNode *node) {
    if (node != nil) {
        string cr, cl, cp;
        cr = cl = cp = "  ";
        cr[0] = '*';
        cr[1] = '~';
        cl[0] = '+';
        cl[1] = '-';
        cp[0] = '|';
        string s = sp; //"tekst do wyświetlenia w wierszach pośrednich dla synów"
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printRecursive(s + cp, cr, node->right);
        s = s.substr(0, sp.length() - 2);
//        string value = node->balance;
        cout << s << sn << "(" << node->balance << ")" << '\n';
        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printRecursive(s + cp, cl, node->left);
    }
}