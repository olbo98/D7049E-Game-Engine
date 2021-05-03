#pragma once
#include "../Utils/Queue.h"
#include "../Utils/SimpleList.h"
#include "Message.h"

class System;

/*!
* The MessageBus takes care of the communication between different systems and should be used by systems that wants to communicate with each other.
*/
class MessageBus
{
public:
	MessageBus();
	~MessageBus();

	//! Adds a system that should recieve messages to the list of subscribed systems
	/*!
	* A System has to be added as a reciever via this function to be able to recieve messages
	* 
	* \param system pointer to the system that should be added
	*/
	void addReciever(System* system);
	//! Adds a message to the message queue
	/*!
	* Adds a message to the message queue. To send these messages to the subscribed systems notify() will have to be called
	* 
	* \param msg pointer to a Message that should be sent to systems
	*/
	void postMessage(Message* msg);
	//! Sends all pending messages to the systems
	/*!
	* Sends the messages in the queue one at a time to each system that has added themselves as recievers.
	*/
	void notify();

private:
	Queue<Message> msgQueue;
	SimpleList<System*> systems;
};
