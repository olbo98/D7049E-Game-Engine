#pragma once
#include "../Utils/Queue.h"
#include "../Utils/SimpleList.h"
#include "Message.h"

namespace MS {
	class System;

	class MessageBus
	{
	public:
		MessageBus();
		~MessageBus();

		void addReciever(System* system); //TODO: Add parameters
		void postMessage(Message* msg);
		void notify();

	private:
		Queue<Message> msgQueue;
		SimpleList<System*> systems; //Pointers
		//TODO: Add reference to systems
	};
}