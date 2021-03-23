#include <iostream>

using namespace std;

struct Node {
    int value{};
    Node *next = nullptr;
};

struct MyList {
    Node *first_element = nullptr;
};

void display(Node *my_node) {
    while (my_node != nullptr) {
        cout << my_node->value << '\n';
        my_node = my_node->next;
    }
}

void add_element_front(MyList *my_list, int value) {
    Node *temp = new Node{value, my_list->first_element};
    my_list->first_element = temp;
}

void add_element_end(MyList *my_list, int value) {
    Node *end = my_list->first_element;
    Node *temp = new Node{value, nullptr};
    if (end != nullptr) {
        while (end != nullptr && end->next == nullptr) {
            end = end->next;
        }
        end->next = temp;
    } else {
        my_list->first_element = temp;
    }
}

void add_element_middle(MyList *my_list, int value, int index) {
    if (index == 0) {
        add_element_front(my_list, value);
        return;
    }
    Node *left = my_list->first_element;
    Node *temp = new Node{value, nullptr};
    if (left != nullptr) {
        for (int i = 0; i < index - 1; ++i) {
            left = left->next;
            if (left->next == nullptr) {
                exit(1);
            }
        }
        Node *right = left->next;
        left->next = temp;
        temp->next = right;
    } else {
        my_list->first_element = temp;
    }
}

void remove_from_list(MyList *myList, int index) {
    Node *left = myList->first_element;
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
        Node *right = left->next->next;
        Node *temp = left->next;
        delete temp;
        left->next = right;
    }
}
