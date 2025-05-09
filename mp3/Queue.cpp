#include "Queue.h"

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(Sarki s) {
    Node* newNode = new Node;
    newNode->data = s;
    newNode->next = nullptr;
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void Queue::dequeue() {
    if (!isEmpty()) {
        Node* temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) {
            rear = nullptr;
        }
    }
}

Sarki Queue::frontElement() {
    if (!isEmpty()) {
        return front->data;
    }
    return Sarki(-1, "", "");
}

bool Queue::isEmpty() {
    return front == nullptr;
}
