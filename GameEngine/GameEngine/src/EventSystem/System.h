#pragma once
#include "Message.h"
#include "MessageBus.h"

namespace MS {
	class System
	{
	public:
		System();
		System(MessageBus* a_msgBus);
		virtual void handleMessage(Message* msg);
	protected:
		MessageBus* msgBus;
	};
}
