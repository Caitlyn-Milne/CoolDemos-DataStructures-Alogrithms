#include "pch.h"
#include <array>

template<typename Iterator0, typename  Iterator1>
bool are_equal(Iterator0 begin_0, Iterator0 end_0, Iterator1 begin_1, Iterator1 end_1)
{
	while (begin_0 != end_0 && begin_1 != end_1)
	{
		const int value_0 = *begin_0;
		const int value_1 = *begin_1;
		if (value_0 != value_1) return false;
		++begin_0;
		++begin_1;
	}

	if (begin_0 != end_0 || begin_1 != end_1)
	{
		return false;
	}

	return true;
}

TEST(MyDynamicList, Indexer_Get_4x8x12_ShouldBe4x8x12)
{
	int items[] = { 4, 8, 12 };
	const ds::MyDynamicList list(items, 3);
	ASSERT_EQ(list[0], 4);
	ASSERT_EQ(list[1], 8);
	ASSERT_EQ(list[2], 12);
}

TEST(MyDynamicList, Indexer_Set_Index1ChangeTo10_ShouldBe4x10x12)
{
	int items[] = { 4, 8, 12 };
	const ds::MyDynamicList list(items, 3);
	list[1] = 10;
	ASSERT_EQ(list[0], 4);
	ASSERT_EQ(list[1], 10);
	ASSERT_EQ(list[2], 12);
}

TEST(MyDynamicList, Indexer_GetExceedingBounds_ShouldThrow)
{
	int items[] = { 4, 8, 12 };
	const ds::MyDynamicList list(items, 3);
	ASSERT_THROW
	( {
		int _ = list[3];
	}, std::exception);
	
}

TEST(MyDynamicList, Indexer_GetBelowBounds_ShouldThrow)
{
	int items[] = { 4, 8, 12 };
	const ds::MyDynamicList list(items, 3);
	ASSERT_THROW
	({
		int _ = list[-1];
		}, std::exception);

}

TEST(MyDynamicList, Constructor_ShouldHaveCapacity2)
{
	const ds::MyDynamicList list(2);
	ASSERT_EQ(list.get_capacity(), 2);
}

TEST(MyDynamicList, Constructor_WithCapacity0_ShouldThrow)
{
	EXPECT_THROW
	({
		const ds::MyDynamicList list(0);
	}, std::exception);
}

TEST(MyDynamicList, Constructor_PresetItems)
{
	int items[] = { 4, 8, 12 };
	const ds::MyDynamicList list(items, 3);
	ASSERT_EQ(list.get_capacity(), 3);
	ASSERT_EQ(list.get_count(), 3);
	ASSERT_EQ(list[0], 4);
	ASSERT_EQ(list[1], 8);
	ASSERT_EQ(list[2], 12);
}

TEST(MyDynamicList, Constructor_Clone)
{
	int items[] = { 4, 8, 12 };
	ds::MyDynamicList list(items, 3);
	const ds::MyDynamicList clone = list;
	ASSERT_EQ(list.get_capacity(), clone.get_capacity());
	ASSERT_EQ(list.get_count(), clone.get_count());
	ASSERT_EQ(list[0], clone[0]);
	ASSERT_EQ(list[1], clone[1]);
	ASSERT_EQ(list[2], clone[2]);

	ASSERT_TRUE(&list != &clone);
	ASSERT_TRUE(&list[0] != &clone[0]);
	ASSERT_TRUE(&list[1] != &clone[1]);
	ASSERT_TRUE(&list[2] != &clone[2]);
}

TEST(MyDynamicList, Constructor_ShouldBe_Empty)
{
	const ds::MyDynamicList list;
	ASSERT_EQ(list.get_count(), 0);
}

TEST(MyDynamicList, Add_3_ShouldBe_3)
{
	ds::MyDynamicList list;
	list.add(3);
	ASSERT_EQ(list.get_at(0), 3);
}

TEST(MyDynamicList, Add_321_ShouldBe_321)
{
	ds::MyDynamicList list;
	list.add(3);
	list.add(2);
	list.add(1);
	ASSERT_EQ(list.get_at(0), 3);
	ASSERT_EQ(list.get_at(1), 2);
	ASSERT_EQ(list.get_at(2), 1);
}

TEST(MyDynamicList, Add_MoreThanCapacity_Should_IncreaseCapacity)
{
	ds::MyDynamicList list(2);
	list.add(1);
	ASSERT_EQ(list.get_capacity(), 2);
	list.add(2);
	ASSERT_EQ(list.get_capacity(), 2);
	list.add(3);
	ASSERT_EQ(list.get_capacity(), 4);
}

TEST(MyDynamicList, RemoveAt_OutOfBounds_ShouldThrow)
{
	EXPECT_THROW
	({
		int items[3];
		items[0] = 1;
		items[1] = 2;
		items[2] = 3;
		ds::MyDynamicList list(items, 3);
		list.remove_at(3);
	}, std::exception);
}

TEST(MyDynamicList, RemoveAt_1_ShouldRemove8)
{
	int items[] = { 4, 8, 12};
	ds::MyDynamicList list(items, 3);

	list.remove_at(1);
	ASSERT_EQ(list.get_count(),2);
	ASSERT_EQ(list[0], 4);
	ASSERT_EQ(list[1], 12);
}

TEST(MyDynamicList, RemoveAll_AlwaysFalse_ShouldBeTheSame)
{
	int items[] = { 2, 4, 6, 8 };
	ds::MyDynamicList list(items, 4);

	const std::function<bool(int)> predicate = [](int _) { return false; };
	list.remove_all(predicate);
	ASSERT_EQ(list.get_count(), 4);
	ASSERT_EQ(list[0], 2);
	ASSERT_EQ(list[1], 4);
	ASSERT_EQ(list[2], 6);
	ASSERT_EQ(list[3], 8);
}

TEST(MyDynamicList, RemoveAll_AlwaysTrue_ShouldBeEmpty)
{
	int items[] = { 2, 4, 6, 8 };
	ds::MyDynamicList list(items, 4);

	const std::function<bool(int)> predicate = [](int _) { return true; };
	list.remove_all(predicate);
	ASSERT_EQ(list.get_count(), 0);
}

TEST(MyDynamicList, RemoveAll_Even_ShouldOnlyContainOdd)
{
	int items[] = { 1, 2, 3, 4, 5 };
	ds::MyDynamicList list(items, 5);

	const std::function<bool(int)> predicate = [](const int i) { return i % 2 == 0; };
	list.remove_all(predicate);
	ASSERT_EQ(list.get_count(), 3);
	ASSERT_EQ(list[0], 1);
	ASSERT_EQ(list[1], 3);
	ASSERT_EQ(list[2], 5);
}

TEST(MyDynamicList, Iterator_NoRemove_ShouldEqualAtIndex)
{
	int items[] = { 1, 2, 3, 4, 5 };
	ds::MyDynamicList list(items, 5);

	int i = 0;
	for(int list_item : list)
	{
		ASSERT_EQ(list_item, items[i++]);
	}
}

TEST(MyDynamicList, Iterator_RemoveLast_ExpectlastToBeMissing)
{
	int items[] = { 1, 2, 3, 4, 5 };
	ds::MyDynamicList list(items, 5);
	list.remove_at(4);

	const std::array<int,4> expected = { 1, 2, 3, 4 };

	const bool equal = are_equal(expected.begin(), expected.end(), list.begin(), list.end());
	ASSERT_TRUE(equal);
}
