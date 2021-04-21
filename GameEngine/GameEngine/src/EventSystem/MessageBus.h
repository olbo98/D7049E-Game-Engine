#pragma once
#include "Message.h"

namespace MS {
	class MessageBus
	{
	public:
		MessageBus();
		~MessageBus();

		void addReciever();
		void postMessage(Message* msg);
	};
}

