#pragma once
#include "Message.h"
#include "System.h"

namespace MS {
	class MessageBus
	{
	public:
		MessageBus();
		~MessageBus();

		void addReciever(System* system); //TODO: Add parameters
		void postMessage(Message* msg);

	private:
		Message msgQueue[2] = {};
		//TODO: Add reference to systems
	};
}

