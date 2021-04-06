#include <iostream>
#include "DoubleList.h"

using namespace std;


DoubleList::DoubleList(int *array, int arraySize) {
    for (unsigned int i = 0; i < arraySize; ++i) {
        addElementBack(array[i]);
    }
}

DoubleList::~DoubleList() {
    while (first_element != nullptr) {
        removeElementFront();
    }
}

/**
 * Add element in front of the list
 * @param value
 */
void DoubleList::addElementFront(int value) {
    size++;
    ListNode *temp = new ListNode{value, this->first_element, this->first_element->next};
    this->first_element = temp;
    temp->prev = this->first_element;
}

/**
 * Add element in back of the list
 * @param value
 */
void DoubleList::addElementBack(int value) {
    size++;
    ListNode *end = this->first_element;
    ListNode *temp = new ListNode{value, this->first_element, nullptr};
    if (end != nullptr) {
        while (end != nullptr && end->next == nullptr) {
            end = end->next;
        }
        end->next = temp;
        temp->prev = end;
    } else {
        this->first_element = temp;
    }
}

/**
 * Add element anywhere in the list
 * @param value
 * @param index
 */
void DoubleList::addElementAnywhere(int value, unsigned int index) {
    size++;
    if (index == 0) {
        addElementFront(value);
        return;
    }
    ListNode *left = this->first_element;
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
        this->first_element = temp;
        temp->prev = this->first_element;
    }
}

/**
 * Remove element in front of the list
 */
void DoubleList::removeElementFront() {
    if (this->first_element == nullptr) {
        return;
    } else {
        size--;
        ListNode *temp = this->first_element->next;
        temp->prev = nullptr;
        delete this->first_element;
        this->first_element = temp;
    }
}

/**
 * Remove element in back of the list
 */
void DoubleList::removeElementBack() {
    if (this->first_element == nullptr) {
        return;
    } else {
        size--;
        ListNode *temp;
        ListNode *end = this->first_element;
        while (end != nullptr && end->next == nullptr) {
            end = end->next;
        }
        temp = end->prev;
        temp->next = nullptr;
        delete end;
    }
}

/**
 * Remove element anywhere in the list
 * @param index
 */
void DoubleList::removeElementAnywhere(unsigned int index) {
    if (this->first_element == nullptr) {
        return;
    } else {
        ListNode *temp;
        ListNode *left = this->first_element;
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
    }
}

/**
 * Remove value from list if exist
 * @param value
 */
void DoubleList::removeValue(int value) {
    ListNode *temp = this->first_element;
    ListNode *temp2;
    while (temp->next != nullptr) {
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
ListNode *DoubleList::findValue(int value) {
    ListNode *temp = this->first_element;
    while (temp->next != nullptr) {
        if (temp->value == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

/**
 * Display all elements in list
 */
void DoubleList::display() {
    ListNode *my_node = this->first_element;
    while (my_node != nullptr) {
        cout << my_node->value << '\n';
        my_node = my_node->next;
    }
}