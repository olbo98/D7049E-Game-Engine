#pragma once
#include "../EventSystem/Messages/Message.h"
#include "../EventSystem/MessageBus.h"
#include "../EntityComponentSystem/EntityComponentDef.h"
#include<set>

/*!
* A virtual system class. Every class that has the role of a system needs 
* to inherit this class to be able to send and recieve messages from other systems. The handleMessage function needs to be overrided and should
* contain logic for how to handle different messages.
* A System contains any functionality that iterates upon a list of entities
* with a certain signature of components.
*/
class System
{
public:
	std::set<Entity> m_entities;
	/*!
	* Should be implemented by all classes that inherits the System class. Should contain functionality to handle incoming messages
	* 
	* \param msg the message that should be handled
	*/
	virtual void handleMessage(Message* msg) = 0;
};

