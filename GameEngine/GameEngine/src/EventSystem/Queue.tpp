#include <cstdio>

namespace MS {
	template <typename T>
	Queue<T>::Queue() {
		lengthOfQueue = 0;
		head = new Node<T>();
		tail = new Node<T>();

		head->value = (T)NULL;
		head->next = tail;

		tail->value = (T)NULL;
		tail->next = head;
	}

	template <typename T>
	void Queue<T>::add(T* value) {
		struct Node<T>* newNode = new Node<T>();
		newNode->next = tail;
		newNode->value = *value;

		if(lengthOfQueue == 0){
			head->next = newNode;
			tail->next = newNode;
		}

		tail->next->next = newNode;
		tail->next = newNode;

		lengthOfQueue++;
	}

	template <typename T>
	T Queue<T>::pop() {
		Node<T>* popedMessage = head->next;

		head->next = popedMessage->next;

		lengthOfQueue--;

		T value = popedMessage->value;

		delete popedMessage;

		return value;
	}

	template <typename T>
	int Queue<T>::getLength() {
		return lengthOfQueue;
	}
}