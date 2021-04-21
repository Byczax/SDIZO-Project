#include <string>
#include "RedBlackTree.h"

using std::string;

/**
 * Node constructor
 * @param val
 * @param p
 * @param l
 * @param r
 * @param givenColor
 */
TreeNode::TreeNode(int val, TreeNode *p, TreeNode *l, TreeNode *r, nodeColor givenColor) {
    value = val;
    parent = p;
    left = l;
    right = r;
    color = givenColor;
}

/**
 * Tree constructor
 * @param array
 * @param arraySize
 */
RedBlackTree::RedBlackTree(const int *array, int arraySize) {
    nil = new TreeNode(0, nullptr, nullptr, nullptr, BLACK);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    for (unsigned int i = 0; i < arraySize; ++i) {
        addValue(array[i]);
    }
}

/**
 * destructor
 */
RedBlackTree::~RedBlackTree() {
    removeNodeFromMemory(root);
    delete nil;
}

/**
 * Remove node from tree memory
 * @param node
 */
void RedBlackTree::removeNodeFromMemory(TreeNode *node) {
    if (node == nil)
        return;
    removeNodeFromMemory(node->left);
    removeNodeFromMemory(node->right);
    delete node;
}

/**
     * add value to tree - algorytm - Cormen - wprowadzenie do algorytmów 13.3
     * @param value
     */
void RedBlackTree::addValue(int value) {
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
     * Fixing the properties of a red-black tree when a number is added to it
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
    // fix root
    while (root->parent != nil) {
        root = root->parent;
    }
    root->color = BLACK;
}
/*
 *     B                 A
 *   /   \      ->     /   \
 *  D     A           B    C
 *      /  \        /  \
 *     E    C      D    E
 */
/**
     * node rotation to left
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
/*
 *        A           B
 *      /   \   ->  /   \
 *     B    C      D     A
 *   /  \              /  \
 *  D    E            E    C
 */
/**
 * node rotation to right
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

/**
 * Remove value from tree
 * @param value
 * @return
 */
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

/**
 * Remove node from tree
 * @param node
 */
void RedBlackTree::removeGivenElement(TreeNode *node) {
    TreeNode *y;
    if (node->left == nil || node->right == nil)
        y = node;
    else {
        // find succesor
        y = node->right;
        while (y->left != nil) {
            y = y->left;
        }
    }
    TreeNode *x;
    // only one son
    if (y->left != nil) {
        x = y->left;
    } else {
        x = y->right;
    }
    if (x != nil)
        x->parent = y->parent;
    if (y->parent == nil) {
        root = x;
    }
    if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    if (y != node) {
        node->value = y->value;
    }

    if (y->color == BLACK)
        removeFixTree(x);
    //remove the reference to the element in the parent of the element to be removed

    delete y;
}

/**
 * Fix tree after node deletion
 * @param node
 */
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

/**
 * Find value in tree
 * @param value
 * @return
 */
bool RedBlackTree::findValue(int value) {
    TreeNode *temp = root;
    while (temp != nil) {
        if (value == temp->value)
            return true;
        else {
            if (value < temp->value)
                temp = temp->left;
            else
                temp = temp->right;
        }
    }
    return false;
}
//-----------------Display tree------------------------------------------------

/**
 * display tree, code from https://eduinf.waw.pl/inf/alg/001_search/0112.php
 */
void RedBlackTree::display() {
    printRecursive("", "", root);
    std::cout << '\n';
}

/**
 * help function
 * @param sp
 * @param sn
 * @param index
 */
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
        string value = (node->color == RED) ? std::to_string(node->value) + "(R)" : std::to_string(node->value) + "(B)";
        printf("%s%s%s\n", s.c_str(), sn.c_str(), value.c_str());
//        cout << s << sn << value << '\n';
        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printRecursive(s + cp, cl, node->left);
    }
}
//-------------------------------------------------------------------------------