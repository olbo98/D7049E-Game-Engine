#pragma once

template <typename T>
class SimpleList
{
public:
	SimpleList();

	void add(T* value);
	T get(int index);
	int getLength();
private:
	int maxLength;
	int currentIndex;
	T* list;

	T* resize(int size);
};

#include "SimpleList.tpp"
