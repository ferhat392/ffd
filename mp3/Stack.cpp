#include "Stack.h"

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(Sarki s) {
    Node* newNode = new Node;
    newNode->data = s;
    newNode->next = top;
    top = newNode;
}

void Stack::pop() {
    if (!isEmpty()) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

Sarki Stack::topElement() {
    if (!isEmpty()) {
        return top->data;
    }
    return Sarki(-1, "", "");
}

bool Stack::isEmpty() {
    return top == nullptr;
}
