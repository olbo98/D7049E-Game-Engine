#pragma once
#include "../Utils/Queue.h"
#include "System.h"
#include "Message.h"

namespace MS {
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
		System systens[10];
		//TODO: Add reference to systems
	};
}