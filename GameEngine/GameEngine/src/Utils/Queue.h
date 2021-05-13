#pragma once

//! A node used in the Queue class
/* 
* The Node class is used to create a linked list. Nodes can be chained together to create a chain with nodes. Each node contains a value
* that it stores as well as a reference to the next node in the chain
*/
template <class T>
class Node {
public:
    T value; //!< The value that the Node should store
    Node<T>* next; //!< A reference to the next node in the chain
};

//! A FIFO queue
/*! 
* The Queue class is a FIFO queue and uses a linked list to achieve this. The queue has two anchors, head and tail. Head and tail always
* points at the first and last item in the queue respectively.
*/
template <class T>
class Queue {
public:
    Queue();

    //! Adds a value to the queue and puts it at the end of the queue
    /*!
    * \param value a pointer to the item that should be added to the queue
    */
    void add(T* item);

    //! Returns the first item in the queue and removes it from the queue
    /*!
    * \return The first item in the queue
    */
    T pop();

    //! Returns the number of items in the queue
    /*!
    * \return Number of items in queue
    */
    int getLength();
private:
    int lengthOfQueue;
    Node<T>* head;
    Node<T>* tail;
};

#include "Queue.tpp"
