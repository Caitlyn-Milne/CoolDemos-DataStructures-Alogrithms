#include "pch.h"
#include <exception>
namespace ds
{
	constexpr int default_capacity = 4;

	my_dynamic_list::iterator::iterator(int* pointer): _pointer(pointer) { }

	//iterator
	my_dynamic_list::iterator& my_dynamic_list::iterator::operator++()
	{
		_pointer++;
		return *this;
	}

	my_dynamic_list::iterator my_dynamic_list::iterator::operator++(int)
	{
		const iterator self = *this;
		++(*this);
		return self;
	}

	my_dynamic_list::iterator& my_dynamic_list::iterator::operator--()
	{
		_pointer--;
		return *this;
	}

	my_dynamic_list::iterator my_dynamic_list::iterator::operator--(int)
	{
		const iterator self = *this;
		--(*this);
		return self;
	}

	int my_dynamic_list::iterator::operator*() const
	{
		return *_pointer;
	}

	int* my_dynamic_list::iterator::operator->() const
	{
		return _pointer;
	}

	my_dynamic_list::iterator::operator int*() const
	{
		return _pointer;
	}

	bool my_dynamic_list::iterator::operator==(const iterator& other) const
	{
		return this->_pointer == other._pointer;
	}

	bool my_dynamic_list::iterator::operator!=(const iterator& other) const
	{
		return !(this->_pointer == other._pointer);
	}

	//constructors
	my_dynamic_list::my_dynamic_list() : my_dynamic_list(default_capacity) { }

	my_dynamic_list::my_dynamic_list(my_dynamic_list& copy)
	{
		_array = new int[copy.get_capacity()];
		_capacity = copy.get_capacity();
		for(const int i : copy)
		{
			add(i);
		}
	}

	my_dynamic_list::my_dynamic_list(const int capacity)
	{
		if (capacity <= 0) throw std::exception("Capacity can't be 0");
		_array = new int[capacity];
		_capacity = capacity;
	}

	my_dynamic_list::my_dynamic_list(int array[], int size_of_array)
	{
		_array = new int[size_of_array];
		for(int i = 0; i < size_of_array; i++)
		{
			_array[i] = array[i];
		}
		_count = size_of_array;
		_capacity = size_of_array;
	}

	//public functions
	void my_dynamic_list::add(const int value)
	{
		ensure_capacity(_count + 1);
		_array[_count++] = value;
	}

	void my_dynamic_list::remove_at(int index)
	{
		validate_in_bounds(index);

		const std::function<bool(int, int)> func = 
			[index](const int _, const int i)
		{
			return index == i;
		};

		remove_all(func);
	}

	void my_dynamic_list::remove_all(const std::function<bool(int)>& predicate)
	{
		const std::function<bool(int, int)> func = [predicate](const int item, const int _)
		{
			return predicate(item);
		};

		remove_all(func);
	}

	void my_dynamic_list::remove_all(const std::function<bool(int, int)>& predicate)
	{
		int left = -1;
		int new_count = 0;
		for (int right = 0; right < _capacity; right++)
		{
			const int value = *(_array + right);

			if (predicate(value, right)) continue;
			
			left++;
			new_count++;

			const int temp = _array[left];
			_array[left] = _array[right];
			_array[right] = temp;
		}
		_count = new_count;
	}

	int& my_dynamic_list::operator[](const int index) const
	{
		validate_in_bounds(index);
		return *(_array + index);
	}

	int my_dynamic_list::get_count() const
	{
		return _count;
	}

	int my_dynamic_list::get_capacity() const
	{
		return _capacity;
	}

	int my_dynamic_list::get_at(const int index) const
	{
		validate_in_bounds(index);
		return *(_array + index);
	}

	void my_dynamic_list::set_at(const int index, const int value) const
	{

		validate_in_bounds(index);
		int* ref = _array + index;
		*ref = value;
	}

	my_dynamic_list::iterator my_dynamic_list::begin()
	{
		return iterator(_array);
	}

	my_dynamic_list::iterator my_dynamic_list::end()
	{
		return iterator(_array + _count);
	}

	my_dynamic_list::~my_dynamic_list()
	{
		delete[] _array;
	}

	//private functions
	void my_dynamic_list::ensure_capacity(const int new_capacity)
	{
		if (new_capacity <= _capacity) return;

		const auto copy = new int[new_capacity];

		for (int i = 0; i < _capacity; i++)
		{
			const int value = *(_array + i);
			copy[i] = value;
		}

		delete[] _array;

		_array = copy;
		_capacity *= 2;
	}

	inline void my_dynamic_list::validate_in_bounds(const int index) const
	{
		if (0 > index || index >= get_count())
		{
			throw std::exception("index out of bounds");
		}
	}
}
