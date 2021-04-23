#pragma once
#include "Message.h"

namespace MS {
    class Queue {
    public:
        Queue();
        ~Queue();

        void add(Message* msg);

        Message pop();

        int getLength();

    private:
        int lengthOfQueue;
        int maxLength;
        int currentIndex;
        Message* queue;

        Message* resize(Message* queue, int size);
    };
}
