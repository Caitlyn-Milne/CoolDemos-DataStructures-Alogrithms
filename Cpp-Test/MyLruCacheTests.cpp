#include "pch.h"

using namespace ds;

constexpr size_t DEFAULT_TEST_CAPACITY = 4;
static_assert(0 != DEFAULT_TEST_CAPACITY); //special tests for this

struct MyLruCacheTest : public Test
{

	std::unique_ptr<MyLruCache<int, string>> lru_cache_;

	void SetUp() override
	{
		lru_cache_ = make_unique<MyLruCache<int, string>>();
		lru_cache_->set_capacity(DEFAULT_TEST_CAPACITY);
	}

	void TearDown() override
	{
		lru_cache_.reset();
	}
};

void GivenEmpty_WhenPutting_ShouldBeInLru(MyLruCache<int, string>& lru)
{
	string five = "five";
	lru.put(5, five);
	ASSERT_TRUE(lru.contains(5));
}

void GivenLessItemsThanCapacity_WhenPutting_ShouldIncreaseSize(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);

	ASSERT_EQ(lru.size(), 0);

	string one = "one";
	lru.put(1, one);
	ASSERT_EQ(lru.size(), 1);

	string two = "two";
	lru.put(2, two);
	ASSERT_EQ(lru.size(), 2);

	string three = "three";
	lru.put(3, three);
	ASSERT_EQ(lru.size(), 3);

	string four = "four";
	lru.put(4, four);
	ASSERT_EQ(lru.size(), 4);
}

void GivenFull_WhenPutting_ShouldRemoveLeastRecentlyUsed(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);
	string one = "one";
	string two = "two";
	string three = "three";
	string four = "four";
	lru.put(1, one);
	lru.put(2, two);
	lru.put(3, three);
	lru.put(4, four);
	ASSERT_TRUE(lru.is_full());

	string five = "five";
	lru.put(5, five);
	ASSERT_FALSE(lru.contains(1));
	ASSERT_TRUE(lru.contains(2));
	ASSERT_TRUE(lru.contains(3));
	ASSERT_TRUE(lru.contains(4));
	ASSERT_TRUE(lru.contains(5));

	lru.get(2); //2 would be lru but it now will be 3

	string six = "six";
	lru.put(6, six);
	ASSERT_FALSE(lru.contains(1));
	ASSERT_FALSE(lru.contains(3));
	ASSERT_TRUE(lru.contains(2));
	ASSERT_TRUE(lru.contains(4));
	ASSERT_TRUE(lru.contains(5));
}

void WhenRemoving_ShouldDecreaseSize(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);
	string one = "one";
	string two = "two";
	string three = "three";
	string four = "four";
	lru.put(1, one);
	lru.put(2, two);
	lru.put(3, three);
	lru.put(4, four);

	ASSERT_EQ(lru.size(), 4);

	lru.remove(4);
	ASSERT_EQ(lru.size(), 3);

	lru.remove(3);
	ASSERT_EQ(lru.size(), 2);

	lru.remove(2);
	ASSERT_EQ(lru.size(), 1);

	lru.remove(1);
	ASSERT_EQ(lru.size(), 0);
}

void GivenItemInLru_WhenRemoving_ShouldNotBeInLru(MyLruCache<int, string>& lru)
{
	lru.set_capacity(2);
	string one = "one";
	string two = "two";
	lru.put(1, one);
	lru.put(2, two);

	lru.remove(1);
	ASSERT_FALSE(lru.contains(1));
	ASSERT_TRUE(lru.contains(2));

	lru.remove(2);
	ASSERT_FALSE(lru.contains(1));
	ASSERT_FALSE(lru.contains(2));
}

void GivenItemNotInLru_WhenRemoving_ShouldThrow(MyLruCache<int, string>& lru)
{
	string five = "five";
	lru.put(5, five);
	ASSERT_THROW({ lru.remove(2); }, std::exception);
}

void GivenEmpty_WhenRemoving_ShouldThrow(MyLruCache<int, string>& lru)
{
	ASSERT_THROW({ lru.remove(2); }, std::exception);
}

void GivenItemNotInLru_WhenGetting_ShouldThrow(MyLruCache<int, string>& lru)
{
	string five = "five";
	lru.put(5, five);
	ASSERT_THROW({ lru.get(2); }, std::exception);
}

void GivenItemInLru_WhenGetting_ShouldGetValue(MyLruCache<int, string>& lru)
{
	string five = "five";
	lru.put(5, five);
	ASSERT_EQ(lru.get(5), five);
}

void WhenCapacityChanged_ShouldGettingCapacityChange(MyLruCache<int, string>& lru)
{
	ASSERT_EQ(lru.get_capacity(), DEFAULT_TEST_CAPACITY);
	lru.set_capacity(DEFAULT_TEST_CAPACITY * 2);
	ASSERT_EQ(lru.get_capacity(), DEFAULT_TEST_CAPACITY * 2);
}

void GivenFull_WhenCapacityShrunk_ShouldRemoveLeastRecentlyUsedElementsUntilNewCapacity(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);
	string one = "one";
	string two = "two";
	string three = "three";
	string four = "four";
	lru.put(1, one);
	lru.put(2, two);
	lru.put(3, three);
	lru.put(4, four);
	ASSERT_EQ(lru.size(), 4);

	lru.set_capacity(2);
	ASSERT_EQ(lru.size(), 2);
	ASSERT_FALSE(lru.contains(1));
	ASSERT_FALSE(lru.contains(2));
	ASSERT_TRUE(lru.contains(3));
	ASSERT_TRUE(lru.contains(4));
}


void GivenFullAndGetUsed_WhenCapacityShrunk_ShouldRemoveLeastRecentlyUsedElementsUntilNewCapacity(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);
	string one = "one";
	string two = "two";
	string three = "three";
	string four = "four";
	lru.put(1, one);
	lru.put(2, two);
	lru.put(3, three);
	lru.put(4, four);
	ASSERT_EQ(lru.size(), 4);

	lru.get(2);

	lru.set_capacity(2);
	ASSERT_EQ(lru.size(), 2);
	ASSERT_FALSE(lru.contains(1));
	ASSERT_TRUE(lru.contains(2));
	ASSERT_FALSE(lru.contains(3));
	ASSERT_TRUE(lru.contains(4));
}

void GivenPreviouslyFull_WhenCapacityGrows_ShouldBeAbleToAddItemsUntilCapacity(MyLruCache<int, string>& lru)
{
	lru.set_capacity(2);
	string one = "one";
	string two = "two";
	lru.put(1, one);
	lru.put(2, two);
	ASSERT_TRUE(lru.is_full());

	lru.set_capacity(4);
	string three = "three";
	string four = "four";
	lru.put(3, three);
	lru.put(4, four);

	ASSERT_TRUE(lru.contains(1));
	ASSERT_TRUE(lru.contains(2));
	ASSERT_TRUE(lru.contains(3));
	ASSERT_TRUE(lru.contains(4));
}

void GivenInLru_WhenGettingItem_ShouldBeMostRecentlyUsed(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);
	string one = "one";
	string two = "two";
	string three = "three";
	string four = "four";
	lru.put(1, one);
	lru.put(2, two);
	lru.put(3, three);
	lru.put(4, four);

	lru.get(2);

	lru.set_capacity(1); //only most recently used element should be in the lru cache when capacity is one
	ASSERT_TRUE(lru.contains(2));
}

void GivenFull_WhenClearing_ShouldBeEmpty(MyLruCache<int, string>& lru)
{
	lru.set_capacity(3);
	string one = "one";
	string two = "two";
	string three = "three";
	lru.put(1, one);
	lru.put(2, two);
	lru.put(3, three);

	ASSERT_FALSE(lru.is_empty());
	ASSERT_TRUE(lru.is_full());

	lru.clear();

	ASSERT_TRUE(lru.is_empty());
	ASSERT_FALSE(lru.is_full());
}

void GivenEmpty_WhenClearing_ShouldBeEmpty(MyLruCache<int, string>& lru)
{
	lru.set_capacity(3);

	ASSERT_TRUE(lru.is_empty());
	ASSERT_FALSE(lru.is_full());

	lru.clear();

	ASSERT_TRUE(lru.is_empty());
	ASSERT_FALSE(lru.is_full());
}

void GivenNeitherFullOrEmpty_WhenClearing_ShouldBeEmpty(MyLruCache<int, string>& lru)
{
	lru.set_capacity(4);
	string one = "one";
	string two = "two";
	lru.put(1, one);
	lru.put(2, two);

	ASSERT_FALSE(lru.is_empty());
	ASSERT_TRUE(lru.is_full());

	lru.clear();

	ASSERT_TRUE(lru.is_empty());
	ASSERT_FALSE(lru.is_full());
}

void GivenEmpty_WhenSetCapacityToZero_ShouldBeFullAndEmpty(MyLruCache<int, string>& lru)
{
	ASSERT_TRUE(lru.is_empty());
	ASSERT_FALSE(lru.is_full());

	lru.set_capacity(0);

	ASSERT_TRUE(lru.is_empty());
	ASSERT_TRUE(lru.is_full());
}

void GivenKeyAlreadyInLru_WhenPutting_Replace(MyLruCache<int, string>& lru)
{
	lru.set_capacity(3);
	string one = "one";
	string two = "two";
	lru.put(1, one);
	lru.put(2, two);

	string ONE = "TWO";
	string TWO = "TWO";
	lru.put(1, ONE);
	lru.put(2, TWO);

	ASSERT_EQ(lru.get(1), ONE);
	ASSERT_EQ(lru.get(2), TWO);
}

TEST_F(MyLruCacheTest, GivenEmpty_WhenPutting_ShouldBeInLru)
{
	GivenEmpty_WhenPutting_ShouldBeInLru(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenLessItemsThanCapacity_WhenPutting_ShouldIncreaseSize)
{
	GivenLessItemsThanCapacity_WhenPutting_ShouldIncreaseSize(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenFull_WhenPutting_ShouldRemoveLeastRecentlyUsed)
{
	GivenFull_WhenPutting_ShouldRemoveLeastRecentlyUsed(*lru_cache_);
}

TEST_F(MyLruCacheTest,WhenRemoving_ShouldDecreaseSize)
{
	WhenRemoving_ShouldDecreaseSize(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenItemInLru_WhenRemoving_ShouldNotBeInLru)
{
	GivenItemInLru_WhenRemoving_ShouldNotBeInLru(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenItemNotInLru_WhenRemoving_ShouldThrow)
{
	GivenItemNotInLru_WhenRemoving_ShouldThrow(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenEmpty_WhenRemoving_ShouldThrow)
{
	GivenEmpty_WhenRemoving_ShouldThrow(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenItemNotInLru_WhenGetting_ShouldThrow)
{
	GivenItemNotInLru_WhenGetting_ShouldThrow(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenItemInLru_WhenGetting_ShouldGetValue)
{
	GivenItemInLru_WhenGetting_ShouldGetValue(*lru_cache_);
}

TEST_F(MyLruCacheTest, WhenCapacityChanged_ShouldGettingCapacityChange)
{
	WhenCapacityChanged_ShouldGettingCapacityChange(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenFull_WhenCapacityShrunk_ShouldRemoveLeastRecentlyUsedElementsUntilNewCapacity)
{
	GivenFull_WhenCapacityShrunk_ShouldRemoveLeastRecentlyUsedElementsUntilNewCapacity(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenFullAndGetUsed_WhenCapacityShrunk_ShouldRemoveLeastRecentlyUsedElementsUntilNewCapacity)
{
	GivenFullAndGetUsed_WhenCapacityShrunk_ShouldRemoveLeastRecentlyUsedElementsUntilNewCapacity(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenPreviouslyFull_WhenCapacityGrows_ShouldBeAbleToAddItemsUntilCapacity)
{
	GivenPreviouslyFull_WhenCapacityGrows_ShouldBeAbleToAddItemsUntilCapacity(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenInLru_WhenGettingItem_ShouldBeMostRecentlyUsed)
{
	GivenInLru_WhenGettingItem_ShouldBeMostRecentlyUsed(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenFull_WhenClearing_ShouldBeEmpty)
{
	GivenFull_WhenClearing_ShouldBeEmpty(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenEmpty_WhenClearing_ShouldBeEmpty)
{
	GivenEmpty_WhenClearing_ShouldBeEmpty(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenNeitherFullOrEmpty_WhenClearing_ShouldBeEmpty)
{
	GivenNeitherFullOrEmpty_WhenClearing_ShouldBeEmpty(*lru_cache_);
}

TEST_F(MyLruCacheTest, GivenEmpty_WhenSetCapacityToZero_ShouldBeFullAndEmpty) //this might happen to turn off caching
{
	GivenEmpty_WhenSetCapacityToZero_ShouldBeFullAndEmpty(*lru_cache_);
}


TEST_F(MyLruCacheTest, GivenKeyAlreadyInLru_WhenPutting_Replace) 
{
	GivenKeyAlreadyInLru_WhenPutting_Replace(*lru_cache_);
}

//todo more 0 capacity tests

//todo what happends when put data with a key that already exsits
