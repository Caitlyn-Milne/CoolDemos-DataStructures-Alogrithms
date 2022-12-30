#pragma once
namespace ds
{
	template<typename Type>
	class IStack
	{
	public:
		virtual ~IStack() = 0;
		virtual void push(Type) = 0;
		virtual Type pop() = 0;
		virtual Type peek_last() = 0;
	};
}
