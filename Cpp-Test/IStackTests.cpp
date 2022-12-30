#include "pch.h"

using namespace ds;


TEST(s,s)
{
	MyLinkedList<int> list;
}
/*struct StackTestParams
{
	explicit StackTestParams(std::shared_ptr<IStack<int>> stack)
	: stack_(std::move(stack)) {}
public:
	std::shared_ptr<IStack<int>> stack_;
};

struct IStackTest : Test, WithParamInterface<StackTestParams>
{
public:
	std::shared_ptr<IStack<int>> get_stack() const
	{
		return GetParam().stack_;
	}
};

INSTANTIATE_TEST_CASE_P
(
	Default,
	IStackTest,
	Values(
		StackTestParams(std::make_shared<MyLinkedList<int>>())
	)
);


TEST_P(IStackTest, Push1Pop_Expect1)
{
	const auto stack = get_stack();
	stack->push(1);
	const int item = stack->pop();
	ASSERT_EQ(item, 1);
}



*/