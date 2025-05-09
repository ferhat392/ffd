#ifndef STACK_H
#define STACK_H

#include "Sarki.h"

class Stack {
private:
    struct Node {
        Sarki data;
        Node* next;
    };

    Node* top;

public:
    Stack();
    ~Stack();

    void push(Sarki s);
    void pop();
    Sarki topElement();
    bool isEmpty();
};

#endif /* STACK_H */
