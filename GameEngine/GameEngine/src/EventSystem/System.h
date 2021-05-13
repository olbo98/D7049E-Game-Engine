#pragma once
#include "Messages/Message.h"
#include "MessageBus.h"

/*!
* A virtual system class. Every class that has the role of a system needs 
* to inherit this class to be able to send and recieve messages from other systems. The handleMessage function needs to be overrided and should
* contain logic for how to handle different messages.
*/
class System
{
public:
	
	virtual void handleMessage(Message* msg) = 0;
protected:
	MessageBus* msgBus;
};

