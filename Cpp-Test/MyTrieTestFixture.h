#pragma once
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