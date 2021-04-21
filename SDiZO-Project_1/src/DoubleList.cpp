#include <iostream>
#include "DoubleList.h"

/**
 * Constructor
 * @param array
 * @param arraySize
 */
DoubleList::DoubleList(int *array, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        addElementBack(array[i]);
    }
}

/**
 * Desctructor
 */
DoubleList::~DoubleList() {
    while (head != nullptr) {
        removeElementFront();
    }
}

/**
 * Add element in front of the list
 * @param value
 */
void DoubleList::addElementFront(int value) {
    ListNode *temp = new ListNode{value, nullptr, this->head};
    if (size == 0) {
        this->head = temp;
        this->tail = temp;
    } else {
        this->head->prev = temp;
        this->head = temp;
    }
    ++size;
}

/**
 * Add element in back of the list
 * @param value
 */
void DoubleList::addElementBack(int value) {

    ListNode *temp = new ListNode{value, this->tail, nullptr};
    if (size == 0) {
        this->head = temp;
        this->tail = temp;
    } else {
        this->tail->next = temp;
        this->tail = temp;
    }
    ++size;
}

/**
 * Add element anywhere in the list
 * @param value
 * @param index
 */
void DoubleList::addElementAnywhere(int value, unsigned int index) {

    if (index == 0) {
        addElementFront(value);
    } else if (index >= size - 1) {
        addElementBack(value);
    } else {
        ListNode *left = this->head;
        ListNode *temp = new ListNode{value, nullptr};
        if (left != nullptr) {
            for (int i = 0; i < index - 1; ++i) {
                left = left->next;
                if (left->next == nullptr) {
                    exit(1);
                }
            }
            ListNode *right = left->next;

            left->next = temp;
            temp->prev = left;
            temp->next = right;
            right->prev = temp;

        } else {
            this->head = temp;
            temp->prev = this->head;
        }
    }
    size++;
}

/**
 * Remove element in front of the list
 */
void DoubleList::removeElementFront() {
    if (size == 0) {
        return;
    } else {
        ListNode *temp = this->head->next;
        if (temp != nullptr) {
            temp->prev = nullptr;
        }
        delete this->head;
        this->head = temp;
        --size;
    }
}

/**
 * Remove element in back of the list
 */
void DoubleList::removeElementBack() {
    if (size == 0) {
        return;
    }else if(size == 1){
        delete this->tail;
    }
    else {
        ListNode *temp = this->tail->prev;
        temp->next = nullptr;
        delete this->tail;
        this->tail = temp;
    }
    --size;
}

/**
 * Remove element anywhere in the list
 * @param index
 */
void DoubleList::removeElementAnywhere(unsigned int index) {
    if (this->head == nullptr) {
        return;
    } else if (index == 0) {
        removeElementFront();
    } else if (index == size - 1) {
        removeElementBack();
    } else {
        ListNode *temp;
        ListNode *left = this->head;
        for (int i = 0; i < index - 1; ++i) {
            left = left->next;
            if (left->next == nullptr) {
                return;
            }
        }
        temp = left->prev;
        temp->next = left->next;
        temp = left->next;
        temp->prev = left->prev;
        delete left;
        --size;
    }
}

/**
 * Remove value from list if exist
 * @param value
 */
void DoubleList::removeValue(int value) {
    ListNode *temp = this->head;
    ListNode *temp2;
    while (temp != nullptr && temp->next != nullptr) {
        if (temp->value == value) {
            temp2 = temp->prev;
            temp2->next = temp->next;
            temp2 = temp->next;
            temp2->prev = temp->prev;
            delete temp;
            return;
        }
        temp = temp->next;
    }
}

/**
 * find element in list
 * @param value
 * @return
 */
int DoubleList::findValue(int value) {
    ListNode *temp = this->head;
    int counter = 0;
    while (temp != nullptr) {
        if (temp->value == value) {
            return counter;
        }
        temp = temp->next;
        ++counter;
    }
    return -1;
}

/**
 * Display all elements in list
 */
void DoubleList::display() {
    if (size == 0) {
        return;
    }
    ListNode *my_node = this->head;
    std::cout << "\n" << my_node->value;
    my_node = my_node->next;
    while (my_node != nullptr) {
        std::cout << " <=> " << my_node->value;
        my_node = my_node->next;
    }
    std::cout << "\n";
}