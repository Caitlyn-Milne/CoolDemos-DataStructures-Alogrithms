#include "pch.h"
using namespace ds;

struct LinkedListQueueTest : public ::testing::Test
{
protected:
	std::unique_ptr<IQueue<int>> queue;

	void SetUp() override
	{
		queue = std::make_unique<MyLinkedList<int>>();
	}

	void TearDown() override
	{
		queue.reset();
	}
};

struct ArrayDequeQueueTest : public ::testing::Test
{
protected:
	std::unique_ptr<IQueue<int>> queue;

	void SetUp() override
	{
		queue = std::make_unique<MyArrayDeque<int>>();
	}

	void TearDown() override
	{
		queue.reset();
	}
};

void WhenOffering_ShouldIncreaseCount(IQueue<int>& queue)
{
	ASSERT_EQ(queue.get_count(), 0);
	queue.offer(1);
	ASSERT_EQ(queue.get_count(), 1);
	queue.offer(2);
	ASSERT_EQ(queue.get_count(), 2);
	queue.offer(3);
	ASSERT_EQ(queue.get_count(), 3);
}

void WhenPolling_ShouldRemoveThemInFifoOrder(IQueue<int>& queue)
{
	queue.offer(1);
	queue.offer(2);
	queue.offer(3);

	ASSERT_EQ(queue.poll(), 1);
	ASSERT_EQ(queue.poll(), 2);
	ASSERT_EQ(queue.poll(), 3);
}

void WhenPolling_ShouldDecreaseCount(IQueue<int>& queue)
{
	queue.offer(1);
	queue.offer(2);
	queue.offer(3);
	ASSERT_EQ(queue.get_count(), 3);

	queue.poll();
	ASSERT_EQ(queue.get_count(), 2);
	queue.poll();
	ASSERT_EQ(queue.get_count(), 1);
	queue.poll();
	ASSERT_EQ(queue.get_count(), 0);
}

void WhenPollingEmpty_ShouldThrow(IQueue<int>& queue)
{
	ASSERT_TRUE(queue.get_count() == 0, "incorrect test set up");
	ASSERT_THROW({ queue.poll(); }, std::exception);
}

void WhenPeekingEmpty_ShouldThrow(IQueue<int>& queue)
{
	ASSERT_TRUE(queue.get_count() == 0, "incorrect test set up");
	ASSERT_THROW({ queue.peek_first(); }, std::exception);
}

void WhenPeeking_ShouldReturnNext(IQueue<int>& queue)
{
	queue.offer(1);
	ASSERT_EQ(queue.peek_first(), 1);
	queue.offer(2);
	ASSERT_EQ(queue.peek_first(), 1);
	queue.offer(3);
	ASSERT_EQ(queue.peek_first(), 1);

	queue.poll();
	ASSERT_EQ(queue.peek_first(), 2);
	queue.poll();
	ASSERT_EQ(queue.peek_first(), 3);
}

/*** MyLinkedList ***/

TEST_F(LinkedListQueueTest, WhenOffering_ShouldIncreaseCount)
{
	WhenOffering_ShouldIncreaseCount(*queue);
}

TEST_F(LinkedListQueueTest, WhenPolling_ShouldRemoveThemInFifoOrder)
{
	WhenPolling_ShouldRemoveThemInFifoOrder(*queue);
}

TEST_F(LinkedListQueueTest, WhenPolling_ShouldDecreaseCount)
{
	WhenPolling_ShouldDecreaseCount(*queue);
}

TEST_F(LinkedListQueueTest, WhenPollingEmpty_ShouldThrow)
{
	WhenPollingEmpty_ShouldThrow(*queue);
}

TEST_F(LinkedListQueueTest, WhenPeekingEmpty_ShouldThrow)
{
	WhenPeekingEmpty_ShouldThrow(*queue);
}

TEST_F(LinkedListQueueTest, WhenPeeking_ShouldReturnNext)
{
	WhenPeeking_ShouldReturnNext(*queue);
}

/*** MyArrayDeque ***/

TEST_F(ArrayDequeQueueTest, WhenOffering_ShouldIncreaseCount)
{
	WhenOffering_ShouldIncreaseCount(*queue);
}

TEST_F(ArrayDequeQueueTest, WhenPolling_ShouldRemoveThemInFifoOrder)
{
	WhenPolling_ShouldRemoveThemInFifoOrder(*queue);
}

TEST_F(ArrayDequeQueueTest, WhenPolling_ShouldDecreaseCount)
{
	WhenPolling_ShouldDecreaseCount(*queue);
}

TEST_F(ArrayDequeQueueTest, WhenPollingEmpty_ShouldThrow)
{
	WhenPollingEmpty_ShouldThrow(*queue);
}

TEST_F(ArrayDequeQueueTest, WhenPeekingEmpty_ShouldThrow)
{
	WhenPeekingEmpty_ShouldThrow(*queue);
}

TEST_F(ArrayDequeQueueTest, WhenPeeking_ShouldReturnNext)
{
	WhenPeeking_ShouldReturnNext(*queue);
}