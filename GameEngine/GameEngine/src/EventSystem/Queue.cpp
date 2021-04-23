#include "Queue.h"

namespace MS {
	Queue::Queue() {
		maxLength = 5;
		lengthOfQueue = 0;
		currentIndex = 0;
		queue = new Message[maxLength];
	}

	Queue::~Queue() {
		delete[] queue;
	}

	void Queue::add(Message* msg) {
		if (lengthOfQueue >= maxLength) {
			queue = resize(queue, maxLength + 5);
		}

		queue[currentIndex] = *msg;
		currentIndex++;
		lengthOfQueue++;
	}

	Message Queue::pop() {
		Message msg = queue[currentIndex - 1];
		currentIndex--;
		lengthOfQueue--;

		if (lengthOfQueue < maxLength - 5) {
			queue = resize(queue, maxLength - 5);
		}

		return msg;
	}

	int Queue::getLength() {
		return lengthOfQueue;
	}

	Message* Queue::resize(Message* queue, int size) {
		int amountToChangeSize = size - maxLength;

		Message* new_queue = new Message[maxLength + amountToChangeSize];

		for (int i = 0; i < lengthOfQueue; i++) {
			new_queue[i] = queue[i];
		}
		maxLength += amountToChangeSize;

		return new_queue;
	}
}