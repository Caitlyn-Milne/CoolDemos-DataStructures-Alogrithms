#include "pch.h"
using namespace ds;

struct LinkedListStackTest : public ::testing::Test
{
protected:
	std::unique_ptr<IStack<int>> stack;

	void SetUp() override
	{
		stack = std::make_unique<MyLinkedList<int>>();
	}

	void TearDown() override
	{
		stack.reset();
	}
};

struct ArrayDequeStackTest : public ::testing::Test
{
protected:
	std::unique_ptr<IStack<int>> stack;

	void SetUp() override
	{
		stack = std::make_unique<MyLinkedList<int>>();
	}

	void TearDown() override
	{
		stack.reset();
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

void GivenCleared_WhenPushed_ShouldContain(IStack<int>& stack)
{
	stack.push(1);
	stack.pop();

	stack.push(2);
	ASSERT_EQ(stack.peek_last(), 2);
}

/*** MyLinkedList ***/

TEST_F(LinkedListStackTest, WhenPushing_ShouldIncreaseCount)
{
	WhenPushing_ShouldIncreaseCount(*stack);
}

TEST_F(LinkedListStackTest, WhenPeeking_ShouldBeLastPushed)
{
	WhenPeeking_ShouldBeLastPushed(*stack);
}

TEST_F(LinkedListStackTest, WhenPopping_ShouldRemoveThemInFiloOrder)
{
	WhenPopping_ShouldRemoveThemInFiloOrder(*stack);
}

TEST_F(LinkedListStackTest, WhenPopping_ShouldDecreaseCount)
{
	WhenPopping_ShouldDecreaseCount(*stack);
}

TEST_F(LinkedListStackTest, WhenPeekingEmpty_ShouldThrow)
{
	WhenPeekingEmpty_ShouldThrow(*stack);
}

TEST_F(LinkedListStackTest, GivenCleared_WhenPopped_ShouldContain)
{
	GivenCleared_WhenPushed_ShouldContain(*stack);
}

/*** MyArrayDeque ***/

TEST_F(LinkedListStackTest, WhenPoppingEmpty_ShouldThrow)
{
	WhenPoppingEmpty_ShouldThrow(*stack);
}

TEST_F(ArrayDequeStackTest, WhenPushing_ShouldIncreaseCount)
{
	WhenPushing_ShouldIncreaseCount(*stack);
}

TEST_F(ArrayDequeStackTest, WhenPeeking_ShouldBeLastPushed)
{
	WhenPeeking_ShouldBeLastPushed(*stack);
}

TEST_F(ArrayDequeStackTest, WhenPopping_ShouldRemoveThemInFiloOrder)
{
	WhenPopping_ShouldRemoveThemInFiloOrder(*stack);
}

TEST_F(ArrayDequeStackTest, WhenPopping_ShouldDecreaseCount)
{
	WhenPopping_ShouldDecreaseCount(*stack);
}

TEST_F(ArrayDequeStackTest, WhenPeekingEmpty_ShouldThrow)
{
	WhenPeekingEmpty_ShouldThrow(*stack);
}

TEST_F(ArrayDequeStackTest, WhenPoppingEmpty_ShouldThrow)
{
	WhenPoppingEmpty_ShouldThrow(*stack);
}

TEST_F(ArrayDequeStackTest, GivenCleared_WhenPopped_ShouldContain)
{
	GivenCleared_WhenPushed_ShouldContain(*stack);
}