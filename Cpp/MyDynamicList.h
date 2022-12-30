#pragma once
#include <functional>

namespace ds
{
	class MyDynamicList
	{
		class Iterator
		{
		public:
			Iterator(int* pointer);

			Iterator& operator++(); //prefix
			Iterator operator++(int); //postfix
			Iterator& operator--(); //prefix
			Iterator operator--(int); //postfix

			int operator*() const;
			int* operator->() const;

			explicit operator int*() const;

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;

		private:
			int* _pointer;
		};

	public:
		MyDynamicList(int array[], int size_of_array);
		MyDynamicList();
		MyDynamicList(MyDynamicList& copy);
		MyDynamicList(int capacity);

		void add(int value);
		void remove_at(int);
		void remove_all(const std::function<bool(int item)>& predicate);
		void remove_all(const std::function<bool(int item,int index)>& predicate);

		int get_count() const;
		int get_capacity() const;

		int& operator[](int index) const; //in a fully implementation you might want to make a proxy object
		int get_at(int index) const;
		void set_at(int index, int value) const;

		Iterator begin();
		Iterator end();

		template<typename t> void test();

		~MyDynamicList();

	private:
		void ensure_capacity();
		inline void validate_in_bounds(int index) const;

	private:
		int* array_;
		int capacity_;
		int count_ = 0;
	};


}

