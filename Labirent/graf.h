#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Node {
    int x, y;
    int cost;
    Node* parent;

    Node(int x, int y, int cost = 0, Node* parent = nullptr);
};

struct Graf {
    int** labirent;
    int rows, cols;
    Node* startNode;
    Node* endNode;

    Graf(int rows, int cols);
    ~Graf();
    void labirentOku(const std::string& filename);
    void setStartEndNode();
    bool isValid(int x, int y);
    Node** getNeighbors(Node* node);
};

struct MyQueue {
    Node** data;
    int frontIdx;
    int backIdx;
    int capacity;
    int size;

    MyQueue(int capacity);
    ~MyQueue();
    void push(Node* node);
    void pop();
    Node* front();
    bool empty();
};

struct MyStack {
    Node** data;
    int topIdx;
    int capacity;

    MyStack(int capacity);
    ~MyStack();
    void push(Node* node);
    void pop();
    Node* top();
    bool empty();
};

bool BFS(Graf& graf, Node** path, int& totalCost, int& attemptCount);
bool DFS(Graf& graf, Node** path, int& totalCost, int& attemptCount);
void cikisYolu(Node** path, int pathSize, const std::string& filename, int attemptCount);

#endif