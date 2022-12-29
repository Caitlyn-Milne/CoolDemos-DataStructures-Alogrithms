#pragma once
#include <array>
#include <functional>

namespace ds
{
	class my_dynamic_list
	{
		class iterator
		{
		public:
			iterator(int* pointer);

			iterator& operator++(); //prefix
			iterator operator++(int); //postfix
			iterator& operator--(); //prefix
			iterator operator--(int); //postfix

			int operator*() const;
			int* operator->() const;

			explicit operator int*() const;

			bool operator==(const iterator& other) const;
			bool operator!=(const iterator& other) const;

		private:
			int* _pointer;
		};

	public:
		my_dynamic_list(int array[], int size_of_array);
		my_dynamic_list();
		my_dynamic_list(my_dynamic_list& copy);
		my_dynamic_list(int capacity);

		void add(int value);
		void remove_at(int);
		void remove_all(const std::function<bool(int item)>& predicate);
		void remove_all(const std::function<bool(int item,int index)>& predicate);

		int get_count() const;
		int get_capacity() const;

		int& operator[](int index) const; //in a fully implementation you might want to make a proxy object
		int get_at(int index) const;
		void set_at(int index, int value) const;

		iterator begin();
		iterator end();

		~my_dynamic_list();

	private:
		void ensure_capacity(int new_capacity);
		inline void validate_in_bounds(int index) const;

	private:
		int* _array;
		int _capacity;
		int _count = 0;
	};

}

