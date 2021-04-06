#include <iostream>

using namespace std;

struct ListNode {
    int value{};
    ListNode *next = nullptr;
};

struct DoubleList {
    ListNode *first_element = nullptr;
};

void display(ListNode *my_node) {
    while (my_node != nullptr) {
        cout << my_node->value << '\n';
        my_node = my_node->next;
    }
}

void add_element_front(DoubleList *my_list, int value) {
    ListNode *temp = new ListNode{value, my_list->first_element};
    my_list->first_element = temp;
}

void add_element_end(DoubleList *my_list, int value) {
    ListNode *end = my_list->first_element;
    ListNode *temp = new ListNode{value, nullptr};
    if (end != nullptr) {
        while (end != nullptr && end->next == nullptr) {
            end = end->next;
        }
        end->next = temp;
    } else {
        my_list->first_element = temp;
    }
}

void add_element_middle(DoubleList *my_list, int value, int index) {
    if (index == 0) {
        add_element_front(my_list, value);
        return;
    }
    ListNode *left = my_list->first_element;
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
        temp->next = right;
    } else {
        my_list->first_element = temp;
    }
}

void remove_from_list(DoubleList *myList, int index) {
    ListNode *left = myList->first_element;
    if (myList->first_element != nullptr) {
        if (index == 0) {
            myList->first_element = myList->first_element->next;
            delete left;
            return;
        }

        for (int i = 0; i < index - 1; ++i) {
            left = left->next;
            if (left->next == nullptr) {
                exit(1);
            }
        }
        ListNode *right = left->next->next;
        ListNode *temp = left->next;
        delete temp;
        left->next = right;
    }
}
