#include "MessageBus.h"
#include "../EntityComponentSystem/System.h"


MessageBus::MessageBus() {}
MessageBus::~MessageBus() {}

void MessageBus::postMessage(Message* msg) {
	msgQueue.push_back(msg);
}

void MessageBus::addReciever(System* system) {
	systems.add(system);
}

void MessageBus::notify() {
	int queueLength = msgQueue.size();
	for (int i = 0; i < queueLength; i++) {
		Message* msg = msgQueue.back();
		for (int j = 0; j < systems.getLength(); j++) {
			System* system = systems.get(j);
			system->handleMessage(msg);
		}
		msgQueue.pop_back();
	}
}
