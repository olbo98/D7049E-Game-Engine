#pragma once
#include "Message.h"

class TestMessage : public Message{
private:
    int data;

public: 
    TestMessage(int* someData);
};