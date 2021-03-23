#pragma once

class Node {
public:
    int value;
    Node *prev;
    Node *next;
};

class MyList {
    Node *first_element = nullptr;
    int size = 0;
public:
    void addElementFront(int value);

    void addElementBack(int value);

    void addElementAnywhere(int value, unsigned int index);

    void removeElementFront();

    void removeElementBack();

    void removeElementAnywhere(unsigned int index);

    void removeValue(int value);

    Node *findValue(int value);

    void display();
};