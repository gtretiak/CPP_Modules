#ifndef ARRAY_TPP
#define ARRAY_TPP
#include <exception>

template <typename T>
Array<T>::Array() {
	this->numbers_ = NULL;
	this->size_ = 0;
}
template <typename T>
Array<T>::Array(unsigned int n) { 
	this->numbers_ = new T[n];
	for (unsigned int i = 0; i < n; i++)
		this->numbers_[i] = T();
	this->size_ = n;
}
template <typename T>
unsigned int	Array<T>::size() const {
	return this->size_;
}
template <typename T>
Array<T>::Array(const Array &An) : size_(An.size_) {
	this->numbers_ = new T[this->size_];
	for (unsigned int i = 0; i < this->size_; i++)
		this->numbers_[i] = An.numbers_[i];
}
template <typename T>
Array<T>	&Array<T>::operator=(const Array<T> &An) {
	if (this != &An)
	{
		this->size_ = An.size_;
		delete [] this->numbers_;
		this->numbers_ = new T[this->size_];
		for (unsigned int i = 0; i < this->size_; i++)
			this->numbers_[i] = An.numbers_[i];
	}
	return (*this);
}
template <typename T>
T	&Array<T>::operator[](unsigned int i) {
	if (i < this->size_)
		return this->numbers_[i];
	else
		throw std::exception();
}
template <typename T>
const T	&Array<T>::operator[](unsigned int i) const {
	if (i < this->size_)
		return this->numbers_[i];
	else
		throw std::exception();
}
template <typename T>
Array<T>::~Array() {
	delete [] this->numbers_;
}

#endif
