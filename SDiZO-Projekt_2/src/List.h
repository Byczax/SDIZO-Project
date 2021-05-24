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

public:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int listSize = 0;


    // Constructor
    List();

    // Destructor
    virtual ~List();

    // Add element to the back of the list
    void addElement(int neighbour, int value);

    [[nodiscard]] int getSize() const;

    [[nodiscard]] int findPair(int neighbour, int value) const;

    // display
    void display() const;

    [[nodiscard]] int findValue(int index) const;

    bool removeElementAnywhere(unsigned int index);

    bool removeElementFront();

    bool removeElementBack();

    bool removePair(int neighbour, int value);

    [[nodiscard]] ListNode *getPair(int index) const;
};

class AdjacencyList {
    int vertices;
    int edges;
    List **adjacencyList;

public:
    [[nodiscard]] int getEdges() const;

    AdjacencyList(int vertices, int edges);

    virtual ~AdjacencyList();

    void addUndirectedEdge(int x, int y, int value);

    void addDirectedEdge(int x, int y, int value);

    void allDisplay();

    [[nodiscard]] int verticesCount() const;

    [[nodiscard]] ListNode *getHead(int index) const;
};