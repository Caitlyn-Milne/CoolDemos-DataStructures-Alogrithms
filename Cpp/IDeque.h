#pragma once
namespace ds
{

	template<typename Type>
	class IDeque : IStack<Type>, IQueue<Type>
	{
	public:
		virtual void add_last(Type) = 0;
		virtual Type remove_last() = 0;
		Type peek_last() override = 0;

		virtual void add_first(Type) = 0;
		virtual Type remove_first() = 0;
		Type peek_first() override = 0;
	};
}
