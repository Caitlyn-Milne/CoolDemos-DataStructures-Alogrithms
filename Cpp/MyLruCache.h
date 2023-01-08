#pragma once

namespace ds
{
	template<typename TKey, typename TValue>
	class MyLruCache
	{
	public:
		size_t size();
		size_t get_capacity();
		void set_capacity(size_t cap);
		void put(const TKey& key, TValue& value);
		TValue& get(const TKey& key);
		void remove(const TKey& key);
		bool contains(const TKey& key);
		void clear();
		bool is_full();
		bool is_empty();
	};

	template <typename TKey, typename TValue>
	size_t MyLruCache<TKey, TValue>::size()
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	size_t MyLruCache<TKey, TValue>::get_capacity()
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::set_capacity(size_t cap)
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::put(const TKey& key, TValue& value)
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	TValue& MyLruCache<TKey, TValue>::get(const TKey& key)
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::remove(const TKey& key)
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	bool MyLruCache<TKey, TValue>::contains(const TKey& key)
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::clear()
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	bool MyLruCache<TKey, TValue>::is_full()
	{
		throw std::exception("todo"); //todo
	}

	template <typename TKey, typename TValue>
	bool MyLruCache<TKey, TValue>::is_empty()
	{
		throw std::exception("todo"); //todo
	}
}
