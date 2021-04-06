#include "RedBlackTree.h"
#include "DoubleList.h"


TreeNode::TreeNode(int val, TreeNode *p, TreeNode *l, TreeNode *r, nodeColour givenColor) {
    value = val;
    parent = p;
    left = l;
    right = r;
    color = givenColor;
}

TreeNode *nil;
TreeNode *root;

void removeNodeFromMemory(TreeNode *node) {
    if (node == nil)
        return;
    removeNodeFromMemory(node->left);
    removeNodeFromMemory(node->right);
    delete node;
}

RedBlackTree::RedBlackTree(const int *array, int arraySize) {
    nil = new TreeNode(0, nullptr, nullptr, nullptr, BLACK);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    for (unsigned int i = 0; i < arraySize; ++i) {
        addElement(array[i]);
    }
}

/**
 * destruktor
 */
RedBlackTree::~RedBlackTree() {
    removeNodeFromMemory(root);
    delete nil;
}

/**
     * dodanie liczby do drzewa - algorytm - Cormen - wprowadzenie do algorytmów 13.3
     * @param number
     */
void RedBlackTree::addElement(int number) {
    TreeNode *y = nil;
    TreeNode *x = root;
    while (x != nil) {
        y = x;
        if (number < x->value)
            x = x->left;
        else
            x = x->right;
    }
    TreeNode *z = new TreeNode(number, y, nil, nil);
    if (y == nil)
        root = z;
    else if (number < y->value) {
        y->left = z;
    } else y->right = z;
    addFixTree(z);
}

/**
     * naprawianie właściwości drzewa czerwono-czarnego po dodaniu do niego liczby - algorytm - Cormen - wprowadzenie do algorytmów 13.3
     * @param z
     */
void RedBlackTree::addFixTree(TreeNode *z) {
    while (z->parent->color == RED) {
        TreeNode *grandparent = z->parent->parent;
        TreeNode *y;
        if (z->parent == grandparent->left) {
            y = grandparent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }
        } else {
            y = grandparent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(grandparent);
            }
        }
    }
//        ważne, bo korzeń po operacjach wyżej może już nie być aktualnym korzeniem
    while (root->parent != nil) {
        root = root->parent;
    }
    root->color = BLACK;
}

/**
     * rotacja danego węzła w lewo, jeśli jest możliwa
     * @param a
     */
void RedBlackTree::rotateLeft(TreeNode *a) {
    if (a == nil)
        return;
    TreeNode *b = a->right;
    TreeNode *parent = a->parent;
    if (b != nil) {
        a->right = b->left;
        b->left = a;
        a->parent = b;
        if (a->right != nil) {
            a->right->parent = a;
        }
        b->parent = parent;
        if (parent != nil) {
            if (a == parent->left) {
                parent->left = b;
            } else if (a == parent->right) {
                parent->right = b;
            }
        }
    }
}

/**
 * rotacja danego węzła w prawo, jeśli jest możliwa
 * @param a
 */
void RedBlackTree::rotateRight(TreeNode *a) {
    if (a == nil)
        return;
    TreeNode *b = a->left;
    TreeNode *parent = a->parent;
    if (b != nil) {
        a->left = b->right;
        b->right = a;
        a->parent = b;
        if (a->left != nil) {
            a->left->parent = a;
        }
        b->parent = parent;
        if (parent != nil) {
            if (a == parent->right) {
                parent->right = b;
            } else if (a == parent->left) {
                parent->left = b;
            }
        }
    }
}