#include <string>
#include "RedBlackTree.h"

using namespace std;

TreeNode::TreeNode(int val, TreeNode *p, TreeNode *l, TreeNode *r, nodeColor givenColor) {
    value = val;
    parent = p;
    left = l;
    right = r;
    color = givenColor;
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

void RedBlackTree::removeNodeFromMemory(TreeNode *node) {
    if (node == nil)
        return;
    removeNodeFromMemory(node->left);
    removeNodeFromMemory(node->right);
    delete node;
}

/**
     * dodanie liczby do drzewa - algorytm - Cormen - wprowadzenie do algorytmów 13.3
     * @param value
     */
void RedBlackTree::addElement(int value) {
    TreeNode *y = nil;
    TreeNode *x = root;
    while (x != nil) {
        y = x;
        if (value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    TreeNode *z = new TreeNode(value, y, nil, nil);
    if (y == nil)
        root = z;
    else if (value < y->value) {
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

bool RedBlackTree::removeValue(int value) {
    TreeNode *temp = root;
    while (temp != nil) {
        if (value == temp->value) {
            removeGivenElement(temp);
            return true;
        } else {
            if (value < temp->value)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }
    return false;
}

void RedBlackTree::removeGivenElement(TreeNode *node) {
    TreeNode *y;
    if (node->left == nil || node->right == nil)
        y = node;
    else {
        //node ma dwóch potomków, y będzie następnikiem node
        y = node->right;
        while (y->left != nil)
            y = y->left;
    }
    TreeNode *x;
    x = y->right;
    if (x != nil)
        x->parent = y->parent;
    if (y->parent == nil) {
        root = x;
    } else if (y == y->parent->left) {
        x = y->parent->left;
    } else x = y->parent->right;
    if (y != node)
        node->value = y->value;
    if (y->color == BLACK)
        removeFixTree(x);
    //usunięcie odniesienia do danego elementu u rodzica usuwanego elementu
    TreeNode *deletedParentNode = y->parent;
    if (deletedParentNode->left == y)
        deletedParentNode->left = nil;
    else
        deletedParentNode->right = nil;
    delete y;
}

void RedBlackTree::removeFixTree(TreeNode *node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            TreeNode *w = node->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                w = node->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                node = node->parent;
            } else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                rotateRight(w);
                w = node->parent->right;
            }
            w->color = node->parent->color;
            node->parent->color = BLACK;
            w->right->color = BLACK;
            rotateLeft(node->parent);
            node = root;
        } else {
            TreeNode *w = node->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                w = node->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                node = node->parent;
            } else if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                rotateLeft(w);
                w = node->parent->left;
            }
            w->color = node->parent->color;
            node->parent->color = BLACK;
            w->left->color = BLACK;
            rotateRight(node->parent);
            node = root;
        }
    }
    node->color = BLACK;
}

bool RedBlackTree::findGivenNumber(int number) {
    TreeNode *temp = root;
    while (temp != nil) {
        if (number == temp->value)
            return true;
        else {
            if (number < temp->value)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }
    return false;
}

void RedBlackTree::display() {
    printRecursive("", "", root);
    cout << '\n';
}

void RedBlackTree::printRecursive(const string &sp, const string &sn, TreeNode *node) {
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
        string value = (node->color == RED) ? to_string(node->value) + "R" : to_string(node->value) + "B";
        cout << s << sn << value << '\n';
        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printRecursive(s + cp, cl, node->left);
    }
}