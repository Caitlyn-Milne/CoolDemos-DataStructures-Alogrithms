#include "pch.h"
using namespace ds;

struct MyTrieTest : public ::testing::Test
{
protected:
	std::unique_ptr<MyTrie> trie;

	void SetUp() override
	{
		trie = std::make_unique<MyTrie>();
	}

	void TearDown() override
	{
		trie.reset();
	}
};

void WhenWordAdded_ShouldContainWord(MyTrie& trie)
{
	trie.add_word("hello");

	ASSERT_TRUE(trie.contains_word("hello"));
}

void WhenWordsAdded_ShouldContainWords(MyTrie& trie)
{
	trie.add_word("hello");
	ASSERT_TRUE(trie.contains_word("hello"));

	trie.add_word("world");
	ASSERT_TRUE(trie.contains_word("world"));

	trie.add_word("heap");
	ASSERT_TRUE(trie.contains_word("heap"));
}

void GivenNonEmpty_WhenWordAdded_ShouldContainOtherWords(MyTrie& trie)
{
	trie.add_word("hello");
	trie.add_word("world");

	trie.add_word("heap");
	ASSERT_TRUE(trie.contains_word("world"));
	ASSERT_TRUE(trie.contains_word("hello"));
	ASSERT_TRUE(trie.contains_word("heap"));
}

void GivenMultipleWords_WhenWordRemoved_ShouldntContainWord(MyTrie& trie)
{
	trie.add_word("hello");
	trie.add_word("world");
	trie.add_word("heap");

	trie.remove_word("heap");
	ASSERT_FALSE(trie.contains_word("heap"));

	trie.remove_word("world");
	ASSERT_FALSE(trie.contains_word("world"));

	trie.remove_word("hello");
	ASSERT_FALSE(trie.contains_word("hello"));
}

void GivenMultipleWords_WhenWordRemoved_ShouldContainOtherWords(MyTrie& trie)
{
	trie.add_word("hello");
	trie.add_word("world");
	trie.add_word("heap");

	trie.remove_word("heap");

	ASSERT_TRUE(trie.contains_word("world"));
	ASSERT_TRUE(trie.contains_word("hello"));
}

void GivenSingleWord_WhenWordRemoved_ShouldBeEmpty(MyTrie& trie)
{
	trie.add_word("hello");
	trie.remove_word("hello");
	//todo
}

void WhenUnknownWordRemoved_ShouldReturnFalse(MyTrie& trie)
{
	ASSERT_FALSE(trie.remove_word("hello"));

	trie.add_word("hello");

	ASSERT_FALSE(trie.remove_word("heap"));
}

void GivenWord_WhenDuplicateWordAdded_ShouldReturnFalse(MyTrie& trie)
{

	trie.add_word("heap");
	trie.add_word("hello");

	ASSERT_FALSE(trie.add_word("heap"));
}

void WhenContainsIsUsedForUnknownWord_ShouldReturnFalse(MyTrie& trie)
{
	ASSERT_FALSE(trie.contains_word("heap"));

	trie.add_word("heap");

	ASSERT_FALSE(trie.contains_word("hello"));
}

void WhenContainsIsUsedForKnownWord_ShouldReturnTrue(MyTrie& trie)
{
	trie.add_word("heap");

	ASSERT_TRUE(trie.contains_word("heap"));
}

void WhenUnknownWordAdded_ShouldReturnTrue(MyTrie& trie)
{
	ASSERT_TRUE(trie.add_word("heap"));
	ASSERT_TRUE(trie.add_word("hello"));
	ASSERT_TRUE(trie.add_word("world"));
}

void WhenKnownWordRemoved_ShouldReturnTrue(MyTrie& trie)
{
	trie.add_word("heap");
	trie.add_word("hello");
	trie.add_word("world");
	ASSERT_TRUE(trie.remove_word("heap"));
	ASSERT_TRUE(trie.remove_word("hello"));
	ASSERT_TRUE(trie.remove_word("world"));
}


TEST_F(MyTrieTest, WhenWordAdded_ShouldContainWord)
{
	WhenWordAdded_ShouldContainWord(*trie);
}

TEST_F(MyTrieTest, WhenWordsAdded_ShouldContainWords)
{
	WhenWordsAdded_ShouldContainWords(*trie);
}

TEST_F(MyTrieTest, GivenNonEmpty_WhenWordAdded_ShouldContainOtherWords)
{
	GivenNonEmpty_WhenWordAdded_ShouldContainOtherWords(*trie);
}

TEST_F(MyTrieTest, GivenMultipleWords_WhenWordRemoved_ShouldntContainWord)
{
	GivenMultipleWords_WhenWordRemoved_ShouldntContainWord(*trie);
}

TEST_F(MyTrieTest, GivenMultipleWords_WhenWordRemoved_ShouldContainOtherWords)
{
	GivenMultipleWords_WhenWordRemoved_ShouldContainOtherWords(*trie);
}

TEST_F(MyTrieTest, GivenSingleWord_WhenWordRemoved_ShouldBeEmpty)
{
	GivenSingleWord_WhenWordRemoved_ShouldBeEmpty(*trie);
}

TEST_F(MyTrieTest, WhenUnknownWordRemoved_ShouldReturnFalse)
{
	WhenUnknownWordRemoved_ShouldReturnFalse(*trie);
}

TEST_F(MyTrieTest, GivenWord_WhenDuplicateWordAdded_ShouldReturnFalse)
{
	GivenWord_WhenDuplicateWordAdded_ShouldReturnFalse(*trie);
}

TEST_F(MyTrieTest, WhenContainsIsUsedForUnknownWord_ShouldReturnFalse)
{
	WhenContainsIsUsedForUnknownWord_ShouldReturnFalse(*trie);
}

TEST_F(MyTrieTest, WhenContainsIsUsedForKnownWord_ShouldReturnTrue)
{
	WhenContainsIsUsedForKnownWord_ShouldReturnTrue(*trie);
}

TEST_F(MyTrieTest, WhenUnknownWordAdded_ShouldReturnTrue)
{
	WhenUnknownWordAdded_ShouldReturnTrue(*trie);
}

TEST_F(MyTrieTest, WhenKnownWordRemoved_ShouldReturnTrue)
{
	WhenKnownWordRemoved_ShouldReturnTrue(*trie);
}