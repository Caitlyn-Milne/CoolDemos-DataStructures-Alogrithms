#include "pch.h"
using namespace ds;

struct LinkedListStackTest : public ::testing::Test
{
protected:
	std::unique_ptr<IStack<int>> link_list;

	void SetUp() override
	{
		link_list = std::make_unique<MyLinkedList<int>>();
	}

	void TearDown() override
	{
		link_list.reset();
	}
};

void WhenPushing_ShouldIncreaseCount(IStack<int>& stack)
{
	ASSERT_EQ(stack.get_count(), 0);

	stack.push(1);
	ASSERT_EQ(stack.get_count(), 1);

	stack.push(2);
	ASSERT_EQ(stack.get_count(), 2);

	stack.push(3);
	ASSERT_EQ(stack.get_count(), 3);
}

void WhenPeeking_ShouldBeLastPushed(IStack<int>& stack)
{
	stack.push(5);
	ASSERT_EQ(stack.peek_last(), 5);

	stack.push(10);
	ASSERT_EQ(stack.peek_last(), 10);

	stack.push(15);
	ASSERT_EQ(stack.peek_last(), 15);
}

void WhenPopping_ShouldRemoveThemInFiloOrder(IStack<int>& stack)
{
	stack.push(5);
	stack.push(10);
	stack.push(15);

	ASSERT_EQ(stack.pop(), 15);
	ASSERT_EQ(stack.pop(), 10);
	ASSERT_EQ(stack.pop(), 5);
}

void WhenPopping_ShouldDecreaseCount(IStack<int>& stack)
{
	stack.push(5);
	stack.push(10);
	stack.push(15);
	ASSERT_EQ(stack.get_count(), 3);

	stack.pop();
	ASSERT_EQ(stack.get_count(), 2);

	stack.pop();
	ASSERT_EQ(stack.get_count(), 1);

	stack.pop();
	ASSERT_EQ(stack.get_count(), 0);
}

void WhenPeekingEmpty_ShouldThrow(IStack<int>& stack)
{
	ASSERT_TRUE(stack.get_count() == 0, "incorrect test set up");
	ASSERT_THROW({ stack.peek_last(); }, std::exception);
}

void WhenPoppingEmpty_ShouldThrow(IStack<int>& stack)
{
	ASSERT_TRUE(stack.get_count() == 0, "incorrect test set up");
	ASSERT_THROW({ stack.pop(); }, std::exception);
}

TEST_F(LinkedListStackTest, WhenPushing_ShouldIncreaseCount)
{
	WhenPushing_ShouldIncreaseCount(*link_list);
}

TEST_F(LinkedListStackTest, WhenPeeking_ShouldBeLastPushed)
{
	WhenPeeking_ShouldBeLastPushed(*link_list);
}

TEST_F(LinkedListStackTest, WhenPopping_ShouldRemoveThemInFiloOrder)
{
	WhenPopping_ShouldRemoveThemInFiloOrder(*link_list);
}

TEST_F(LinkedListStackTest, WhenPopping_ShouldDecreaseCount)
{
	WhenPopping_ShouldDecreaseCount(*link_list);
}

TEST_F(LinkedListStackTest, WhenPeekingEmpty_ShouldThrow)
{
	WhenPeekingEmpty_ShouldThrow(*link_list);
}

TEST_F(LinkedListStackTest, WhenPoppingEmpty_ShouldThrow)
{
	WhenPoppingEmpty_ShouldThrow(*link_list);
}