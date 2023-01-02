#pragma once
#include "Interfaces.h"


template<typename Type>
class MyArrayDeque final : public ds::IDeque<Type>
{
public:
	MyArrayDeque();
private:
	Type* array_;
	int capacity_ = 4;
	int front_ = 0;
	int back_ = 0;
	int count_ = 0;
public:
	void add_last(const Type&) override;
	const Type& remove_last() override;
	const Type& peek_last() override;

	void add_first(const Type&) override;
	const Type& remove_first() override;
	const Type& peek_first() override;

	int get_count() override;

	~MyArrayDeque() override;

private:
	void ensure_capacity();
	int last_index() const;
	int first_index() const;

};

template <typename Type>
MyArrayDeque<Type>::MyArrayDeque()
{
	array_ = new Type [4];
	capacity_ = 4;
}

template <typename Type>
void MyArrayDeque<Type>::add_last(const Type& data)
{
	if (count_ != 0)
	{
		++back_;
	}
	++count_;
	ensure_capacity();
	Type copy = data;
	array_[last_index()] = copy;
	
}

template <typename Type>
const Type& MyArrayDeque<Type>::remove_last()
{
	if (get_count() == 0) throw std::exception("empty deque");
	const Type& result = array_[last_index()];
	--back_;
	--count_;
	return result;
}

template <typename Type>
const Type& MyArrayDeque<Type>::peek_last()
{
	if (get_count() == 0) throw std::exception("empty deque");
	const Type& result = array_[last_index()];
	return result;
}

template <typename Type>
void MyArrayDeque<Type>::add_first(const Type& data)
{
	if (count_ != 0)
	{
		--front_;
	}
	++count_;
	ensure_capacity();
	Type copy = data;
	array_[first_index()] = copy;
	
}

template <typename Type>
const Type& MyArrayDeque<Type>::remove_first()
{
	if (get_count() == 0) throw std::exception("empty deque");
	const Type& result = array_[first_index()];
	++front_;
	--count_;
	return result;
}

template <typename Type>
const Type& MyArrayDeque<Type>::peek_first()
{
	if (get_count() == 0) throw std::exception("empty deque");
	const Type& result = array_[first_index()];
	return result;
}

template <typename Type>
int MyArrayDeque<Type>::get_count()
{
	return count_;
}

template <typename Type>
MyArrayDeque<Type>::~MyArrayDeque()
{
	delete[] array_;
}

template <typename Type>
void MyArrayDeque<Type>::ensure_capacity()
{
	if(count_ <= capacity_)
	{
		return;
	}
	const int new_capacity = capacity_ * 2;
	Type* copy = new Type [new_capacity];

	for (int index = 0; index < capacity_; index++)
	{
		int old_index = (front_ + index + capacity_) % capacity_;
		copy[index] = array_[old_index];
	}
	back_ -= front_;
	front_ = 0;
	delete[] array_;
	array_ = copy;
	capacity_ = new_capacity;
}

template <typename Type>
int MyArrayDeque<Type>::last_index() const
{
	return (back_ + capacity_) % capacity_;
}

template <typename Type>
int MyArrayDeque<Type>::first_index() const
{
	return (front_ + capacity_) % capacity_;
}