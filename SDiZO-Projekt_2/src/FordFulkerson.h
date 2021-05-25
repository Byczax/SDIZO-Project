#pragma once

struct slistEl {
    slistEl *next;
    int data;

// Definicja typu obiektowego queue
//---------------------------------
public:

};

class queue {
private:
    slistEl *head;
    slistEl *tail;
public:
    queue();  // konstruktor
    ~queue(); // destruktor
    bool empty();

    int front();

    void push(int v);

    void pop();
};
class FordFulkerson {
    static void ffMatrix();

    static void display();
};
