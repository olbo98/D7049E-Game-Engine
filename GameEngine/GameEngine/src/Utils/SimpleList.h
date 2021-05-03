#pragma once

//! A simple generic list class
/*!
* A simple generic list that resizes itself depending on the number of items in the list
*/
template <typename T>
class SimpleList
{
public:
	/*! Initializes an array with 5 items and sets the starting max length to 5 */
	SimpleList();

	//! Adds an item to the list
	/*!
	* Adds an item to the list. If there are no more free spaces in the list it will increase it's size with 5
	* 
	* \param value the item to be added to the list
	*/
	void add(T value);
	//! Returns the item at the specified index in the list
	/*!
	* \param index index of the item to be returned
	*/
	T get(int index);
	//! Returns the number of elements in the list
	/*!
	* \return number of items in list
	*/
	int getLength();
private:
	int maxLength;
	int currentIndex;
	T* list;

	T* resize(int size);
};

#include "SimpleList.tpp"
