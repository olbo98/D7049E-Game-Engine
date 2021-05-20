#pragma once
#include "./Messages/Message.h"

class TestMessage : public Message{
private:
    int data;

public: 
    TestMessage(int* someData);
};