#include "Queue.h"

namespace MS {
	Queue::Queue() {
		lengthOfQueue = 0;
		struct Node initHead;
		struct Node initTail;

		head = &initHead;
		tail = &initTail;

		head->msg = Message::NULL_MESSAGE;
		head->next = tail;

		tail->msg = Message::NULL_MESSAGE;
		tail->next = head;
	}

	Queue::~Queue() {}

	void Queue::add(Message* msg) {
		struct Node* parent = tail->next;
		struct Node newNode;
		newNode.next = tail;
		newNode.msg = *msg;

		parent->next = &newNode;
		tail->next = &newNode;

		lengthOfQueue++;
	}

	Message Queue::pop() {
		Node* popedMessage = head->next;

		head->next = popedMessage->next;

		popedMessage->next = NULL;

		lengthOfQueue--;

		return popedMessage->msg;
	}

	int Queue::getLength() {
		return lengthOfQueue;
	}
}