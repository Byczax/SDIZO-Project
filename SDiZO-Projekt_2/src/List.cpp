#include <iostream>
#include "List.h"

/**
 * Constructor
 * @param array
 * @param arraySize
 */
List::List() {
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

/**
 * Destructor
 */
List::~List() {
    while (head != nullptr) {
        removeElementFront();
    }
}

/**
 * Add element in back of the list
 * @param value
 */
void List::addElement(int neighbour, int value) {
    auto *temp = new ListNode{neighbour, value, this->tail, nullptr};
    if (listSize == 0) {
        this->head = temp;
        this->tail = temp;
    } else {
        this->tail->next = temp;
        this->tail = temp;
    }
    ++listSize;
}


bool List::removePair(int neighbour, int value) {
    if (listSize == 0) {
        return false;
    } else {
        int index = findPair(neighbour, value);
        if (index) {
            removeElementAnywhere(index);
            return true;
        }
        return false;
    }
}


int List::getSize() const {
    return listSize;
}

int List::findPair(int neighbour, int value) {
    ListNode *temp = this->head;
    int counter = 0;
    while (temp != nullptr) {
        if (temp->neighbour == neighbour && temp->edgeWeight == value) {
            return counter;
        }
        temp = temp->next;
        ++counter;
    }
    return -1;
}

/**
 * find element in list
 * @param index
 * @return
 */
int List::findValue(int index) {
    ListNode *temp = this->head;
    for (int i = 0; i < index; ++i) {
        if (temp != nullptr) {
            temp = temp->next;
        }
    }
    if (temp != nullptr) {
        return temp->edgeWeight;
    }
    return -1;
}

ListNode *List::getPair(int index) {
    ListNode *temp = this->head;
    for (int i = 0; i < index; ++i) {
        if (temp != nullptr) {
            temp = temp->next;
        }
    }
    if (temp != nullptr) {
        return temp;
    }
    return nullptr;
}

/**
 * Remove element in front of the list
 */
bool List::removeElementFront() {
    if (listSize == 0) {
        return false;
    } else {
        ListNode *temp = this->head->next;
        if (temp != nullptr) {
            temp->prev = nullptr;
        }
        delete this->head;
        this->head = temp;
        --listSize;
        return true;
    }
}

/**
 * Remove element in back of the list
 */
bool List::removeElementBack() {
    if (listSize == 0) {
        return false;
    } else if (listSize == 1) {
        delete this->tail;
    } else {
        ListNode *temp = this->tail->prev;
        temp->next = nullptr;
        delete this->tail;
        this->tail = temp;
    }
    --listSize;
    return true;
}

/**
 * Remove element anywhere in the list
 * @param index
 */
bool List::removeElementAnywhere(unsigned int index) {
    if (index >= listSize) {
        return false;
    }
    if (this->head == nullptr) {
        return false;
    } else if (index == 0) {
        removeElementFront();
    } else if (index == listSize - 1) {
        removeElementBack();
    } else {
        ListNode *temp;
        ListNode *left = this->head;
        for (int i = 0; i < index; ++i) {
            left = left->next;
            if (left->next == nullptr) {
                return true;
            }
        }
        temp = left->prev;
        temp->next = left->next;
        temp = left->next;
        temp->prev = left->prev;
        delete left;
        --listSize;
    }
    return false;
}

AdjacencyList::AdjacencyList(int vertices, int edges) {
    this->vertices = vertices;
    this->edges = edges;
    this->adjacencyList = new List *[vertices];
    for (int i = 0; i < vertices; ++i) {
        this->adjacencyList[i] = new List();
    }
}

void AdjacencyList::addUndirectedEdge(int x, int y, int value) {
    adjacencyList[x]->addElement(y, value);
    adjacencyList[y]->addElement(x, value);
    ++edges;
}

void AdjacencyList::addDirectedEdge(int x, int y, int value) {
    adjacencyList[x]->addElement(y, value);
    ++edges;
}

/**
 * Display all elements in list
 */
void List::display() {
    if (listSize == 0) {
        return;
    }
    ListNode *my_node = this->head;
    std::cout << "[" << my_node->neighbour << ", " << my_node->edgeWeight << "]";
    my_node = my_node->next;
    while (my_node != nullptr) {
        std::cout << " <=> " << "[" <<  my_node->neighbour << ", " << my_node->edgeWeight << "]";
        my_node = my_node->next;
    }
    std::cout << "\n";
}

void AdjacencyList::allDisplay() {
    for (int i = 0; i < this->vertices; ++i) {
        std::cout << i << " | ";
        this->adjacencyList[i]->display();
    }
}

int AdjacencyList::verticesCount() const {
    return vertices;
}
