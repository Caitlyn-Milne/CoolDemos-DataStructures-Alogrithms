#include "pch.h"
using namespace ds;

struct LinkedListDequeTest : public ::testing::Test
{
protected:
	std::unique_ptr<IDeque<int>> deque;

	void SetUp() override
	{
		deque = std::make_unique<MyLinkedList<int>>();
	}

	void TearDown() override
	{
		deque.reset();
	}
};

struct ArrayDequeTest : public ::testing::Test
{
protected:
	std::unique_ptr<IDeque<int>> deque;

	void SetUp() override
	{
		deque = std::make_unique<MyArrayDeque<int>>();
	}

	void TearDown() override
	{
		deque.reset();
	}
};

void GivenEmpty_WhenAddingFirst_ShouldBeFirstAndLast(IDeque<int>& deque)
{
	deque.add_first(5);
	ASSERT_EQ(deque.peek_first(), 5);
	ASSERT_EQ(deque.peek_last(), 5);
}

void WhenAddingFirst_ShouldIncreaseCount(IDeque<int>& deque)
{
	ASSERT_EQ(deque.get_count(), 0);

	deque.add_first(5);
	ASSERT_EQ(deque.get_count(), 1);

	deque.add_first(10);
	ASSERT_EQ(deque.get_count(), 2);

	deque.add_first(15);
	ASSERT_EQ(deque.get_count(), 3);
}

void WhenAddingFirst_ShouldBeFirst(IDeque<int>& deque)
{
	deque.add_first(5);
	ASSERT_EQ(deque.peek_first(), 5);

	deque.add_first(10);
	ASSERT_EQ(deque.peek_first(), 10);

	deque.add_first(15);
	ASSERT_EQ(deque.peek_first(), 15);

	ASSERT_EQ(deque.peek_last(), 5);
}

void WhenRemovingFirst_ShouldRemoveInOrder(IDeque<int>& deque)
{
	deque.add_first(3); //[3]
	deque.add_first(2); //[2] [3]
	deque.add_first(1); //[1] [2] [3]

	ASSERT_EQ(deque.remove_first(), 1);
	ASSERT_EQ(deque.remove_first(), 2);
	ASSERT_EQ(deque.remove_first(), 3);
}

void WhenRemovingFirst_ShouldDecreaseCount(IDeque<int>& deque)
{
	deque.add_first(1);
	deque.add_first(2); 
	deque.add_first(3);
	ASSERT_EQ(deque.get_count(), 3);

	deque.remove_first();
	ASSERT_EQ(deque.get_count(), 2);

	deque.remove_first();
	ASSERT_EQ(deque.get_count(), 1);

	deque.remove_first();
	ASSERT_EQ(deque.get_count(), 0);
}

void GivenSize2_WhenRemovingFirst_ShouldHaveEqualFirstAndLast(IDeque<int>& deque)
{
	deque.add_first(5);
	deque.add_first(10);
	ASSERT_EQ(deque.get_count(), 2);

	deque.remove_first();
	ASSERT_EQ(deque.peek_first(), deque.peek_last());
	ASSERT_EQ(deque.peek_first(), 5);
}

void GivenEmpty_WhenRemovingFirst_ShouldThrow(IDeque<int>& deque)
{
	ASSERT_THROW({ deque.remove_first(); }, std::exception);
}

void GivenEmpty_WhenPeekingFirst_ShouldThrow(IDeque<int>& deque)
{
	ASSERT_THROW({ deque.peek_first(); }, std::exception);
}

void GivenEmpty_WhenAddingLast_ShouldBeFirstAndLast(IDeque<int>& deque)
{
	deque.add_last(5);
	ASSERT_EQ(deque.peek_first(), 5);
	ASSERT_EQ(deque.peek_last(), 5);
}

void WhenAddingLast_ShouldIncreaseCount(IDeque<int>& deque)
{
	ASSERT_EQ(deque.get_count(), 0);

	deque.add_last(5);
	ASSERT_EQ(deque.get_count(), 1);

	deque.add_last(10);
	ASSERT_EQ(deque.get_count(), 2);

	deque.add_last(15);
	ASSERT_EQ(deque.get_count(), 3);
}

void WhenAddingFirst_ShouldBeLast(IDeque<int>& deque)
{
	deque.add_last(5);
	ASSERT_EQ(deque.peek_last(), 5);

	deque.add_last(10);
	ASSERT_EQ(deque.peek_last(), 10);

	deque.add_last(15);
	ASSERT_EQ(deque.peek_last(), 15);

	ASSERT_EQ(deque.peek_first(), 5);
}

void WhenRemovingLast_ShouldRemoveReverseInOrder(IDeque<int>& deque)
{
	deque.add_first(3); //[3]
	deque.add_first(2); //[2] [3]
	deque.add_first(1); //[1] [2] [3]

	ASSERT_EQ(deque.remove_last(), 3);
	ASSERT_EQ(deque.remove_last(), 2);
	ASSERT_EQ(deque.remove_last(), 1);
}

void WhenRemovingLast_ShouldDecreaseCount(IDeque<int>& deque)
{
	deque.add_last(1);
	deque.add_last(2);
	deque.add_last(3);
	ASSERT_EQ(deque.get_count(), 3);

	deque.remove_last();
	ASSERT_EQ(deque.get_count(), 2);

	deque.remove_last();
	ASSERT_EQ(deque.get_count(), 1);

	deque.remove_last();
	ASSERT_EQ(deque.get_count(), 0);
}

void GivenSize2_WhenRemovingLast_ShouldHaveEqualFirstAndLast(IDeque<int>& deque)
{
	deque.add_last(5);
	deque.add_last(10);
	ASSERT_EQ(deque.get_count(), 2);

	deque.remove_last();
	ASSERT_EQ(deque.peek_first(), deque.peek_last());
	ASSERT_EQ(deque.peek_last(), 5);
}

void GivenEmpty_WhenRemovingLast_ShouldThrow(IDeque<int>& deque)
{
	ASSERT_THROW({ deque.remove_last(); }, std::exception);
}

void GivenEmpty_WhenPeekingLast_ShouldThrow(IDeque<int>& deque)
{
	ASSERT_THROW({ deque.peek_last(); }, std::exception);
}

/*** MyLinkedList ***/

TEST_F(LinkedListDequeTest, GivenEmpty_WhenAddingLast_ShouldBeFirstAndLast)
{
	GivenEmpty_WhenAddingLast_ShouldBeFirstAndLast(*deque);
}

TEST_F(LinkedListDequeTest, WhenAddingLast_ShouldIncreaseCount)
{
	WhenAddingLast_ShouldIncreaseCount(*deque);
}

TEST_F(LinkedListDequeTest, WhenAddingFirst_ShouldBeLast)
{
	WhenAddingFirst_ShouldBeLast(*deque);
}

TEST_F(LinkedListDequeTest, WhenRemovingLast_ShouldRemoveReverseInOrder)
{
	WhenRemovingLast_ShouldRemoveReverseInOrder(*deque);
}

TEST_F(LinkedListDequeTest, WhenRemovingLast_ShouldDecreaseCount)
{
	WhenRemovingLast_ShouldDecreaseCount(*deque);
}

TEST_F(LinkedListDequeTest, GivenSize2_WhenRemovingLast_ShouldHaveEqualFirstAndLast)
{
	GivenSize2_WhenRemovingLast_ShouldHaveEqualFirstAndLast(*deque);
}

TEST_F(LinkedListDequeTest, GivenEmpty_WhenRemovingLast_ShouldThrow)
{
	GivenEmpty_WhenRemovingLast_ShouldThrow(*deque);
}

TEST_F(LinkedListDequeTest, GivenEmpty_WhenPeekingLast_ShouldThrow)
{
	GivenEmpty_WhenPeekingLast_ShouldThrow(*deque);
}

TEST_F(LinkedListDequeTest, GivenEmpty_WhenAddingFirst_ShouldBeFirstAndLast)
{
	GivenEmpty_WhenAddingFirst_ShouldBeFirstAndLast(*deque);
}

TEST_F(LinkedListDequeTest, WhenAddingFirst_ShouldIncreaseCount)
{
	WhenAddingFirst_ShouldIncreaseCount(*deque);
}

TEST_F(LinkedListDequeTest, WhenAddingFirst_ShouldBeFirst)
{
	WhenAddingFirst_ShouldBeFirst(*deque);
}

TEST_F(LinkedListDequeTest, WhenRemovingFirst_ShouldRemoveInOrder)
{
	WhenRemovingFirst_ShouldRemoveInOrder(*deque);
}

TEST_F(LinkedListDequeTest, WhenRemovingFirst_ShouldDecreaseCount)
{
	WhenRemovingFirst_ShouldDecreaseCount(*deque);
}

TEST_F(LinkedListDequeTest, GivenSize2_WhenRemovingFirst_ShouldHaveEqualFirstAndLast)
{
	GivenSize2_WhenRemovingFirst_ShouldHaveEqualFirstAndLast(*deque);
}

TEST_F(LinkedListDequeTest, GivenEmpty_WhenRemovingFirst_ShouldThrow)
{
	GivenEmpty_WhenRemovingFirst_ShouldThrow(*deque);
}

TEST_F(LinkedListDequeTest, GivenEmpty_WhenPeekingFirst_ShouldThrow)
{
	GivenEmpty_WhenPeekingFirst_ShouldThrow(*deque);
}

/*** MyArrayDeque ***/

TEST_F(ArrayDequeTest, GivenEmpty_WhenAddingLast_ShouldBeFirstAndLast)
{
	GivenEmpty_WhenAddingLast_ShouldBeFirstAndLast(*deque);
}

TEST_F(ArrayDequeTest, WhenAddingLast_ShouldIncreaseCount)
{
	WhenAddingLast_ShouldIncreaseCount(*deque);
}

TEST_F(ArrayDequeTest, WhenAddingFirst_ShouldBeLast)
{
	WhenAddingFirst_ShouldBeLast(*deque);
}

TEST_F(ArrayDequeTest, WhenRemovingLast_ShouldRemoveReverseInOrder)
{
	WhenRemovingLast_ShouldRemoveReverseInOrder(*deque);
}

TEST_F(ArrayDequeTest, WhenRemovingLast_ShouldDecreaseCount)
{
	WhenRemovingLast_ShouldDecreaseCount(*deque);
}

TEST_F(ArrayDequeTest, GivenSize2_WhenRemovingLast_ShouldHaveEqualFirstAndLast)
{
	GivenSize2_WhenRemovingLast_ShouldHaveEqualFirstAndLast(*deque);
}

TEST_F(ArrayDequeTest, GivenEmpty_WhenRemovingLast_ShouldThrow)
{
	GivenEmpty_WhenRemovingLast_ShouldThrow(*deque);
}

TEST_F(ArrayDequeTest, GivenEmpty_WhenPeekingLast_ShouldThrow)
{
	GivenEmpty_WhenPeekingLast_ShouldThrow(*deque);
}

TEST_F(ArrayDequeTest, GivenEmpty_WhenAddingFirst_ShouldBeFirstAndLast)
{
	GivenEmpty_WhenAddingFirst_ShouldBeFirstAndLast(*deque);
}

TEST_F(ArrayDequeTest, WhenAddingFirst_ShouldIncreaseCount)
{
	WhenAddingFirst_ShouldIncreaseCount(*deque);
}

TEST_F(ArrayDequeTest, WhenAddingFirst_ShouldBeFirst)
{
	WhenAddingFirst_ShouldBeFirst(*deque);
}

TEST_F(ArrayDequeTest, WhenRemovingFirst_ShouldRemoveInOrder)
{
	WhenRemovingFirst_ShouldRemoveInOrder(*deque);
}

TEST_F(ArrayDequeTest, WhenRemovingFirst_ShouldDecreaseCount)
{
	WhenRemovingFirst_ShouldDecreaseCount(*deque);
}

TEST_F(ArrayDequeTest, GivenSize2_WhenRemovingFirst_ShouldHaveEqualFirstAndLast)
{
	GivenSize2_WhenRemovingFirst_ShouldHaveEqualFirstAndLast(*deque);
}

TEST_F(ArrayDequeTest, GivenEmpty_WhenRemovingFirst_ShouldThrow)
{
	GivenEmpty_WhenRemovingFirst_ShouldThrow(*deque);
}

TEST_F(ArrayDequeTest, GivenEmpty_WhenPeekingFirst_ShouldThrow)
{
	GivenEmpty_WhenPeekingFirst_ShouldThrow(*deque);
}