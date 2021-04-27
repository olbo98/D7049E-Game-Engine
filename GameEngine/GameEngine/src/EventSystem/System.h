#pragma once
#include "MessageBus.h"

namespace MS {
	class System
	{
	public:
		void handleMessage(Message* msg);
	private:
		MessageBus* msgBus;
	};
}
