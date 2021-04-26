#pragma once
#include "Message.h"
#define NULL nullptr

namespace MS {
    struct Node {
        Message msg;
        Node* next;
    };

    class Queue {
    public:
        Queue();

        void add(Message* msg);

        Message pop();

        int getLength();
    private:
        int lengthOfQueue;
        struct Node* head;
        struct Node* tail;
    };
}
