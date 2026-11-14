#pragma once

template <typename T>
class Array final
{
public:
	Array();
	Array(int capacity);
	~Array();

	Array(const Array& other);
	Array& operator=(const Array& other);

	Array(Array&& other);
	Array& operator=(Array&& other);

	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	const T& operator[](int index) const;
	T& operator[](int index);
	int size() const;

	class Iterator;
	class ConstIterator;

	Iterator iterator();
	ConstIterator iterator() const;
	
	Iterator reverseIterator();
	ConstIterator reverseIterator() const;

	int capacity() const;
private:
	T* _ptr = nullptr;
	int _capacity = 0;
	int _size = 0;

	void swap(Array<T>& other);
};

template <typename T>
class Array<T>::ConstIterator final {
public:
	ConstIterator(Array<T>& array);
	ConstIterator(Array<T>& array, bool forward);

	const T& get() const;
	bool hasNext() const;
	void next();
private:
	bool _forward = true;
	T* _curPtr;
	Array<T>& _array;
};

template <typename T>
class Array<T>::Iterator final {
public:
	Iterator(Array<T>& array);
	Iterator(Array<T>& array, bool forward);

	void set(const T& value);
	const T& get() const;
	bool hasNext() const;
	void next();
private:
	bool _forward = true;
	T* _curPtr;
	Array<T>& _array;
};

template <typename T>
Array<T>::Array() : Array(8) {

}

template <typename T>
Array<T>::Array(int capacity) : _size{ 0 }, _capacity{ capacity } {
	_ptr = static_cast<T*>(operator new(capacity * sizeof(T)));
}

template <typename T>
Array<T>::~Array() {
	for (int i = 0; i < _size; i++) {
		_ptr[i].~T();
	}
	operator delete(_ptr);
}

template <typename T>
Array<T>::Array(const Array& other) : _size(other.size), _capacity(other._capacity) {
	_ptr = operator new(_capacity * sizeof(T));

	for (int i = 0; i < _size; i++) {
		new(_ptr[i]) T(other._ptr[i]);
	}
}

template <typename T>
void Array<T>::swap(Array<T>& other)
{
	std::swap(_ptr, other._ptr);
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
}

// TODO: copy-swap
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
	if (&other != this) {
		Array<T> copy(other);
		swap(copy);
	}
	return *this;
}

template <typename T>
Array<T>::Array(Array&& other){
	swap(other);
}
template <typename T>
Array<T>& Array<T>::operator=(Array&& other) {
	if (&other != this) {
		Array<T> temp{ std::move(other) };
		swap(temp);
	}
	return *this;
}

template <typename T>
int Array<T>::insert(const T& value) {
	return insert(_size, value);
}
template <typename T>
int Array<T>::insert(int index, const T& value) {
	if (_size >= _capacity) {
		_capacity *= 2;
		T* newPtr = static_cast<T*>(operator new(_capacity * sizeof(T)));
		for (int i = 0; i < _size; i++) {
			new(newPtr + i) T(std::move_if_noexcept(_ptr[i]));
			_ptr[i].~T();
		}
		operator delete(_ptr);
		_ptr = newPtr;
	}

	for (int i = _size; i > index; i--) {
		new(_ptr + i) T(std::move_if_noexcept(_ptr[i - 1]));
		_ptr[i - 1].~T();
	}

	new(_ptr + index) T(value);
	_size++;
	return index;
}
template <typename T>
void Array<T>::remove(int index) {
	for (int i = index; i < _size - 1; i++) {
		_ptr[i].~T();
		new(_ptr + i) T(std::move(_ptr[i + 1]));
	}
	_ptr[_size - 1].~T();
	_size--;
}

template <typename T>
const T& Array<T>::operator[](int index) const {
	return _ptr[index];
}
template <typename T>
T& Array<T>::operator[](int index) {
	return _ptr[index];
}

template <typename T>
int Array<T>::size() const {
	return _size;
}

template <typename T>
typename Array<T>::Iterator Array<T>::iterator() {
	return Iterator(*this);
}
template <typename T>
typename Array<T>::ConstIterator Array<T>::iterator() const {
	return ConstIterator(*this);
}

template <typename T>
typename Array<T>::Iterator Array<T>::reverseIterator() {
	return Iterator(*this, false);
}
template <typename T>
typename Array<T>::ConstIterator Array<T>::reverseIterator() const {
	return ConstIterator(*this, false);
}

template <typename T>
int Array<T>::capacity() const {
	return _capacity;
}


template <typename T>
Array<T>::ConstIterator::ConstIterator(Array<T>& array) : ConstIterator(array, true) {}
template <typename T>
Array<T>::ConstIterator::ConstIterator(Array<T>& array, bool forward) {
	_forward = forward;
	_array = array;

	if (_forward) {
		_curPtr = _array._ptr;
	}
	else {
		_curPtr = _array._ptr + (_array._size - 1);
	}
}
template <typename T>
const T& Array<T>::ConstIterator::get() const {
	return *_curPtr;
}
template <typename T>
bool Array<T>::ConstIterator::hasNext() const {
	if (_forward) {
		return *_curPtr != _array._ptr + (_array._size - 1);
	}
	else {
		return *_curPtr != _array._ptr;
	}
}
template <typename T>
void Array<T>::ConstIterator::next() {
	if (_forward) {
		_curPtr++;
	}
	else {
		_curPtr--;
	}
}


template <typename T>
Array<T>::Iterator::Iterator(Array<T>& array) : Iterator(array, true) {}
template <typename T>
Array<T>::Iterator::Iterator(Array<T>& array, bool forward) : _array(array) {
	_forward = forward;

	if (_forward) {
		_curPtr = _array._ptr;
	}
	else {
		_curPtr = _array._ptr + _array._size;
	}
}
template <typename T>
void Array<T>::Iterator::set(const T& value) {
	*_curPtr = value;
}
template <typename T>
const T& Array<T>::Iterator::get() const {
	return *_curPtr;
}
template <typename T>
bool Array<T>::Iterator::hasNext() const {
	if (_forward) {
		return _curPtr != _array._ptr + (_array._size - 1);
	}
	else {
		return _curPtr != _array._ptr;
	}
}
template <typename T>
void Array<T>::Iterator::next() {
	if (_forward) {
		_curPtr++;
	}
	else {
		_curPtr--;
	}
}