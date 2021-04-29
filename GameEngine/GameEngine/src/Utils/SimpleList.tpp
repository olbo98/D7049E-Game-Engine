template <typename T>
SimpleList<T>::SimpleList() {
	list = new T[5];
	maxLength = 5;
	currentIndex = 0;
}

template <typename T>
void SimpleList<T>::add(T value) {
	if (currentIndex == maxLength) {
		list = resize(maxLength + 5);
	}
	
	list[currentIndex] = value;
	currentIndex++;
}

template <typename T>
T SimpleList<T>::get(int index) {
	T value = list[index];
	return value;
}

template <typename T>
T* SimpleList<T>::resize(int size) {
	int amountToResize = maxLength - size;
	T* resizedList = new T[maxLength + amountToResize];

	for (int i = 0; i < currentIndex; i++) {
		resizedList[i] = list[i];
	}

	delete[] list;

	return resizedList;
}

template <typename T>
int SimpleList<T>::getLength(){
	return currentIndex;
}