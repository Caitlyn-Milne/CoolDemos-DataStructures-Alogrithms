#pragma once
namespace ds
{
	template<typename Type>
	class IQueue
	{
	public:
		virtual ~IQueue() = 0;
		virtual void offer(Type) = 0;
		virtual Type poll() = 0;
		virtual Type peek_first() = 0;
	};
}
