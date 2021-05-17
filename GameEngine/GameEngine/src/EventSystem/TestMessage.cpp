#include "TestMessage.h"

TestMessage::TestMessage(int* someData){
    data = *someData;
    id = MessageId::INPUT;
}