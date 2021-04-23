#include "MessageBus.h"

namespace MS {
	MessageBus::MessageBus() {}
	MessageBus::~MessageBus() {}

	void MessageBus::postMessage(Message* msg) {
		msgQueue[0] = *msg;
	}
}