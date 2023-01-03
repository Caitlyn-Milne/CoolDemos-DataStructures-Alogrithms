#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>


using namespace std;
namespace ds
{
	class MyTrie
	{
	public:
		class Node
		{
		private:
			char character_; //'\0' for end of word '\2 for root'
			vector<shared_ptr<Node>> nodes_;

		public:
			explicit Node(char character);

			[[nodiscard]] char get_character() const;
			[[nodiscard]] bool find(char c, shared_ptr<Node>& out_result) const;
			shared_ptr<Node>  add(char c);
			[[nodiscard]] bool end_of_word() const;
			[[nodiscard]] size_t child_count() const;
			bool remove_node(const Node& node);
		};

	private:
		shared_ptr<Node> root_;

	public:
		MyTrie();
		bool add_word(const string& str);
		[[nodiscard]] bool contains_word(const string& str) const;
		bool remove_word(const string& str);
	private:
		static bool remove_word_dfs(const string& str, shared_ptr<Node> parent, size_t i);
	};

}
