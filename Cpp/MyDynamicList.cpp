#include "pch.h"
#include <exception>
namespace ds
{
	constexpr int default_capacity = 4;

	MyDynamicList::Iterator::Iterator(int* pointer): _pointer(pointer) { }

	//iterator
	MyDynamicList::Iterator& MyDynamicList::Iterator::operator++()
	{
		_pointer++;
		return *this;
	}

	MyDynamicList::Iterator MyDynamicList::Iterator::operator++(int)
	{
		const Iterator self = *this;
		++(*this);
		return self;
	}

	MyDynamicList::Iterator& MyDynamicList::Iterator::operator--()
	{
		_pointer--;
		return *this;
	}

	MyDynamicList::Iterator MyDynamicList::Iterator::operator--(int)
	{
		const Iterator self = *this;
		--(*this);
		return self;
	}

	int MyDynamicList::Iterator::operator*() const
	{
		return *_pointer;
	}

	int* MyDynamicList::Iterator::operator->() const
	{
		return _pointer;
	}

	MyDynamicList::Iterator::operator int*() const
	{
		return _pointer;
	}

	bool MyDynamicList::Iterator::operator==(const Iterator& other) const
	{
		return _pointer == other._pointer;
	}

	bool MyDynamicList::Iterator::operator!=(const Iterator& other) const
	{
		return !(_pointer == other._pointer);
	}

	//constructors
	MyDynamicList::MyDynamicList() : MyDynamicList(default_capacity) { }

	MyDynamicList::MyDynamicList(MyDynamicList& copy)
	{
		array_ = new int[copy.get_capacity()];
		capacity_ = copy.get_capacity();
		for(const int i : copy)
		{
			add(i);
		}
	}

	MyDynamicList::MyDynamicList(const int capacity)
	{
		if (capacity <= 0) throw std::exception("Capacity can't be 0");
		array_ = new int[capacity];
		capacity_ = capacity;
	}

	MyDynamicList::MyDynamicList(int array[], int size_of_array)
	{
		array_ = new int[size_of_array];
		for(int i = 0; i < size_of_array; i++)
		{
			array_[i] = array[i];
		}
		count_ = size_of_array;
		capacity_ = size_of_array;
	}

	//public functions
	void MyDynamicList::add(const int value)
	{
		++count_;
		ensure_capacity();
		array_[count_ - 1] = value;
	}

	void MyDynamicList::remove_at(int index)
	{
		validate_in_bounds(index);

		const std::function<bool(int, int)> func = 
			[index](const int _, const int i)
		{
			return index == i;
		};

		remove_all(func);
	}

	void MyDynamicList::remove_all(const std::function<bool(int)>& predicate)
	{
		const std::function<bool(int, int)> func = [predicate](const int item, const int _)
		{
			return predicate(item);
		};

		remove_all(func);
	}

	void MyDynamicList::remove_all(const std::function<bool(int, int)>& predicate)
	{
		int left = -1;
		int new_count = 0;
		for (int right = 0; right < capacity_; right++)
		{
			const int value = *(array_ + right);

			if (predicate(value, right)) continue;
			
			left++;
			new_count++;

			const int temp = array_[left];
			array_[left] = array_[right];
			array_[right] = temp;
		}
		count_ = new_count;
	}

	int& MyDynamicList::operator[](const int index) const
	{
		validate_in_bounds(index);
		return *(array_ + index);
	}

	int MyDynamicList::get_count() const
	{
		return count_;
	}

	int MyDynamicList::get_capacity() const
	{
		return capacity_;
	}

	int MyDynamicList::get_at(const int index) const
	{
		validate_in_bounds(index);
		return *(array_ + index);
	}

	void MyDynamicList::set_at(const int index, const int value) const
	{

		validate_in_bounds(index);
		int* ref = array_ + index;
		*ref = value;
	}

	MyDynamicList::Iterator MyDynamicList::begin()
	{
		return Iterator(array_);
	}

	MyDynamicList::Iterator MyDynamicList::end()
	{
		return Iterator(array_ + count_);
	}

	MyDynamicList::~MyDynamicList()
	{
		delete[] array_;
	}

	//private functions
	void MyDynamicList::ensure_capacity()
	{
		if (count_ <= capacity_) return;

		const int new_capacity = capacity_ * 2;
		const auto copy = new int[new_capacity];

		for (int i = 0; i < capacity_; i++)
		{
			const int value = *(array_ + i);
			copy[i] = value;
		}

		delete[] array_;

		array_ = copy;
		capacity_ = new_capacity;
	}

	inline void MyDynamicList::validate_in_bounds(const int index) const
	{
		if (0 > index || index >= get_count())
		{
			throw std::exception("index out of bounds");
		}
	}
}
