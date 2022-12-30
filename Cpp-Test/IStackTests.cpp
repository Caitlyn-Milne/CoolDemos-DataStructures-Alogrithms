#include "pch.h"
using namespace ds;

struct LinkedListStackTest : public ::testing::Test
{
protected:
	std::unique_ptr<IStack<int>> link_list;

	void SetUp() override {
		// Set the member variable to an instance of a concrete class
		link_list = std::make_unique<MyLinkedList<int>>();
	}

	void TearDown() override {
		link_list.reset();
	}
};

void Push3PeekExpect3(IStack<int>& stack)
{
	stack.push(3);
	const int& item = stack.peek_last();
	ASSERT_EQ(item, 3);
	ASSERT_EQ(stack.get_count(), 1);
}

void Push42PopExpect42(IStack<int>& stack)
{
	stack.push(42);
	const int& item = stack.pop();
	ASSERT_EQ(item, 42);
	ASSERT_EQ(stack.get_count(), 0);
}

void Push1Push2Push3PopExpect3(IStack<int>& stack)
{
	stack.push(1);
	stack.push(2);
	stack.push(3);
	const int& item = stack.pop();
	ASSERT_EQ(item, 3);
	ASSERT_EQ(stack.get_count(), 2);
}

void Push1Push2Push3PopPopExpect3Then2(IStack<int>& stack)
{
	stack.push(1);
	stack.push(2);
	stack.push(3);
	int item = stack.pop();
	ASSERT_EQ(item, 3);
	ASSERT_EQ(stack.get_count(), 2);
	item = stack.pop();
	ASSERT_EQ(item, 2);
	ASSERT_EQ(stack.get_count(), 1);
}

void PeekEmptyStackExpectThrow(IStack<int>& stack)
{
	ASSERT_TRUE(stack.get_count() == 0, "incorrect test set up");
	ASSERT_THROW({ stack.peek_last(); }, std::exception);
}

void PopEmptyStackExpectThrow(IStack<int>& stack)
{
	ASSERT_TRUE(stack.get_count() == 0, "incorrect test set up");
	ASSERT_THROW({ stack.pop(); }, std::exception);
}

TEST_F(LinkedListStackTest, WhenPush3Peek_Expect3)
{
	Push3PeekExpect3(*link_list);
}

TEST_F(LinkedListStackTest, WhenPush42Pop_Expect42)
{
	Push42PopExpect42(*link_list);
}

TEST_F(LinkedListStackTest, WhenPush1Push2Push3Pop_Expect3)
{
	Push1Push2Push3PopExpect3(*link_list);
}

TEST_F(LinkedListStackTest, WhenPush1Push2Push3PopPop_Expect3Then2)
{
	Push1Push2Push3PopExpect3(*link_list);
}

TEST_F(LinkedListStackTest, WhenPeekingEmptyStack_ShouldThrow)
{
	PeekEmptyStackExpectThrow(*link_list);
}

TEST_F(LinkedListStackTest, WhenPoppingEmptyStack_ShouldThrow)
{
	PopEmptyStackExpectThrow(*link_list);
}