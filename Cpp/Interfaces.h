#pragma once
namespace ds
{
	template<typename Type>
	class IStack
	{
	public:
		virtual ~IStack() = default;
		virtual void push(const Type&) = 0;
		virtual const Type& pop() = 0;
		virtual const Type& peek_last() = 0;
		virtual int get_count() = 0;
	};

	template<typename Type>
	class IQueue
	{
	public:
		virtual ~IQueue() = default;
		virtual void offer(const Type&) = 0;
		virtual const Type& poll() = 0;
		virtual const Type& peek_first() = 0;
		virtual int get_count() = 0;
	};

	template<typename Type>
	class IDeque : public IStack<Type>, public IQueue<Type>
	{
	public:
		virtual void add_last(const Type&) = 0;
		virtual const Type& remove_last() = 0;
		const Type& peek_last() override = 0;

		virtual void add_first(const Type&) = 0;
		virtual const Type& remove_first() = 0;
		const Type& peek_first() override = 0;

		int get_count() override = 0;

		void offer(const Type&) final;
		const Type& poll() final;
		void push(const Type&) final;
		const Type& pop() final;

		~IDeque() override = default;

	};

	template <typename Type>
	void IDeque<Type>::offer(const Type& item)
	{
		add_last(item);
	}

	template <typename Type>
	const Type& IDeque<Type>::poll()
	{
		return remove_first();
	}

	template <typename Type>
	void IDeque<Type>::push(const Type& item)
	{
		add_last(item);
	}

	template <typename Type>
	const Type& IDeque<Type>::pop()
	{
		return remove_last();
	}
}
