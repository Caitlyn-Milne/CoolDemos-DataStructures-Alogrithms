#pragma once

namespace ds
{
	const int DEFAULT_CAPACITY = 4;

	template<typename TKey, typename TValue>
	class MyLruCache
	{
		size_t capacity_ = DEFAULT_CAPACITY;
		uint64_t time_ = 0;
		std::unordered_map<TKey, uint64_t> key_to_last_used;
		std::map<uint64_t, TKey> last_used_to_key;
		std::unordered_map<TKey, TValue> key_to_value;

		void remove_excess();
		uint64_t get_time();
		
	public:
		size_t size();
		size_t get_capacity() const;
		void set_capacity(size_t capacity);

		void put(const TKey& key, TValue& value);
		TValue& get(const TKey& key);
		void remove(const TKey& key);
		bool contains(const TKey& key);
		void clear();
		bool is_full();
		bool is_empty();
	};

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::remove_excess()
	{
		while(size() > get_capacity())
		{
			auto& [last_used, key] = *last_used_to_key.begin();
			key_to_value.erase(key);
			key_to_last_used.erase(key);
			last_used_to_key.erase(last_used);
		}
	}

	template <typename TKey, typename TValue>
	uint64_t MyLruCache<TKey, TValue>::get_time()
	{
		return ++time_;
	}

	template <typename TKey, typename TValue>
	size_t MyLruCache<TKey, TValue>::size()
	{
		return key_to_value.size();
	}

	template <typename TKey, typename TValue>
	size_t MyLruCache<TKey, TValue>::get_capacity() const
	{
		return capacity_;
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::set_capacity(size_t capacity)
	{
		capacity_ = capacity;
		remove_excess();
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::put(const TKey& key, TValue& value)
	{
		if (contains(key))
		{
			uint64_t old_time = key_to_last_used[key];
			last_used_to_key.erase(old_time);
		}
		uint64_t time = get_time();
		key_to_value[key] = value;
		key_to_last_used[key] = time;
		last_used_to_key[time] = key;

		remove_excess();
	}

	template <typename TKey, typename TValue>
	TValue& MyLruCache<TKey, TValue>::get(const TKey& key)
	{
		auto got = key_to_value.find(key);
		if (got == key_to_value.end())
		{
			throw std::exception("key not in lru");
		}
		uint64_t old_time = key_to_last_used[key];
		last_used_to_key.erase(old_time);
		uint64_t new_time = get_time();
		key_to_last_used[key] = new_time;
		last_used_to_key[new_time] = key;
		return (*got).second;
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::remove(const TKey& key)
	{
		auto got = key_to_last_used.find(key);
		if (got == key_to_last_used.end())
		{
			throw std::exception("key not in lru");
		}
		auto [_, time] = *got;
		last_used_to_key.erase(time);
		key_to_last_used.erase(key);
		key_to_value.erase(key);
	}

	template <typename TKey, typename TValue>
	bool MyLruCache<TKey, TValue>::contains(const TKey& key)
	{
		return key_to_value.find(key) != key_to_value.end();
	}

	template <typename TKey, typename TValue>
	void MyLruCache<TKey, TValue>::clear()
	{
		key_to_value.clear();
		last_used_to_key.clear();
		key_to_last_used.clear();
		time_ = 0;
	}

	template <typename TKey, typename TValue>
	bool MyLruCache<TKey, TValue>::is_full()
	{
		return size() == get_capacity();
	}

	template <typename TKey, typename TValue>
	bool MyLruCache<TKey, TValue>::is_empty()
	{
		return size() == 0;
	}
}
