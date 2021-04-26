#pragma once

namespace MS {
    template <class T>
    class Node {
    public:
        T value;
        Node<T>* next;
    };

    template <class T>
    class Queue {
    public:
        Queue<T>();

        void add(T* value);
        T pop();
        int getLength();
    private:
        int lengthOfQueue;
        struct Node<T>* head;
        struct Node<T>* tail;
    };
}

#include "Queue.tpp"
