#ifndef QUEUE_H
#define QUEUE_H

#include "Sarki.h"

class Queue {
private:
    struct Node {
        Sarki data;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    Queue();
    ~Queue();

    void enqueue(Sarki s);
    void dequeue();
    Sarki frontElement();
    bool isEmpty();
};

#endif /* QUEUE_H */
