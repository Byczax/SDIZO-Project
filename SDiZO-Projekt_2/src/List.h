#pragma once


class ListNode {
public:
    int neighbour;
    int edgeWeight;
    ListNode *prev;
    ListNode *next;

//    ListNode(int neighbour, int edgeWeight, ListNode *prev = nullptr, ListNode *next = nullptr);
};

class List {
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int listSize = 0;

public:
    // Constructor
    List();

    // Destructor
    virtual ~List();

    // Add element to the back of the list
    void addElement(int neighbour, int value);

    int getSize() const;

    int findPair(int neighbour, int value);

    // display
    void display();

    int findValue(int index);

    bool removeElementAnywhere(unsigned int index);

    bool removeElementFront();

    bool removeElementBack();

    bool removePair(int neighbour, int value);

    ListNode *getPair(int index);
};




class AdjacencyList {
    int vertices;
    int edges;
    List **adjacencyList;
public:
    AdjacencyList(int vertices, int edges);

    void addUndirectedEdge(int x, int y, int value);

    void addDirectedEdge(int x, int y, int value);

    void allDisplay();

    int verticesCount() const;
};