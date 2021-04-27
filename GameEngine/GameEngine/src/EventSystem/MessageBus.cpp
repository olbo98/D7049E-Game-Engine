#include "MessageBus.h"
#include <thread>

using namespace std;

namespace MS {
	MessageBus::MessageBus() {}
	MessageBus::~MessageBus() {}

	void MessageBus::postMessage(Message* msg) {
		msgQueue.add(msg);
	}

	void MessageBus::addReciever(System* system) {
		systems.add(system);
	}

	void MessageBus::notify() {
		int queueLength = msgQueue.getLength();
		for (int i = 0; i < queueLength; i++) {
			Message msg = msgQueue.pop();
			for (int j = 0; j < systems.getLength(); j++) {
				System system = systems.get(j);
				system.handleMessage(&msg);
			}
		}
	}
}