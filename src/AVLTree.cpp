#include "AVLTree.h"
#include <iostream>

using std::string;
using std::cout;


AVLTree::AVLTreeNode::AVLTreeNode() {
}
/**
 * Node constructor
 * @param val
 */
AVLTree::AVLTreeNode::AVLTreeNode(int val) {
    value = val;
    left = right = nullptr;
    balance = 0;
}

/**
 * Node deconstructor
 */
AVLTree::AVLTreeNode::~AVLTreeNode() {
    value = 0;
    left = right = nullptr;
    balance = 0;
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

/**
 * Rotate node to left
 * @param node
 */
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

/**
 * Rotate node to left
 * @param node
 */
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

/**
 * Incremente balance of the node
 * @param node
 * @return
 */
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

/**
 * Decremente balance of the node
 * @param node
 * @return
 */
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

/**
 * Insert value in tree
 * @param data
 * @param node
 * @return
 */
bool AVLTree::insertValue(int data, AVLTreeNode *&node) {
    if (node == nil) {
        node = new AVLTreeNode(data);
        node->left = nil;
        node->right = nil;
        return true;
    } else if (data > node->value) {
        return insertValue(data, node->right) && incrementBalance(node);
    } else if (data < node->value) {
        return insertValue(data, node->left) && decrementBalance(node);
    }
    return false;
}

/**
 * Return minimal value in tree
 * @param node
 * @return
 */
int AVLTree::getMin(AVLTreeNode *node)
{
    AVLTreeNode *temp = node;

    while (temp->left != nil)
        temp = temp->left;

    return temp->value;
}

/**
 * Remove value from the tree
 * @param data
 * @param node
 * @return
 */
bool AVLTree::removeValue(int data, AVLTreeNode *&node)
{
    if (node == nil)
        return false;
    else if (node->value < data)
        return removeValue(data, node->right) && !decrementBalance(node);
    else if (node->value > data)
        return removeValue(data, node->left) && !incrementBalance(node);
    else
    {
        if (node->left == nil && node->right == nil)
        {
            AVLTreeNode *nodeToRemove = node;
            node = nil;
            deleteNode(nodeToRemove);
        }
        else if (node->left != nil && node->right != nil)
        {
            AVLTreeNode *currentNode = node;
            int minNodeValue = getMin(node->right);

            bool isHeightChanged = removeValue(minNodeValue, node);
            currentNode->value = minNodeValue;

            return isHeightChanged;
        }
        else
        {
            AVLTreeNode *nodeToRemove = node;

            if (node->left == nil)
            {
                node = nodeToRemove->right;
                nodeToRemove->right = nil;
            }
            else
            {
                node = nodeToRemove->left;
                nodeToRemove->left = nil;
            }

            deleteNode(nodeToRemove);
        }

        return true;
    }
}

/**
 * Find value in tree
 * @param value
 * @return
 */
AVLTree::AVLTreeNode *AVLTree::findValue(int value) {
    AVLTreeNode *node = root;

    while (node != nil) {
        if (node->value > value) {
            node = node->left;
        } else if (node->value < value) {
            node = node->right;
        } else {
            return node;
        }
    }

    return nullptr;
}
//-----------------Display tree------------------------------------------------

/**
 * display tree, code from https://eduinf.waw.pl/inf/alg/001_search/0112.php
 */
void AVLTree::display() {
    printRecursive("", "", root);
    cout << '\n';
}

/**
 * help function
 * @param sp
 * @param sn
 * @param index
 */
void AVLTree::printRecursive(const string &sp, const string &sn, AVLTreeNode *node) {
    if (node != nil) {
        string cr, cl, cp;
        cr = cl = cp = "  ";
        cr[0] = '*';
        cr[1] = '~';
        cl[0] = '+';
        cl[1] = '-';
        cp[0] = '|';
        string s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printRecursive(s + cp, cr, node->right);
        s = s.substr(0, sp.length() - 2);
        cout << s << sn << node->value << "(" << node->balance << ")" << '\n';
        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printRecursive(s + cp, cl, node->left);
    }
}
//-------------------------------------------------------------------------------