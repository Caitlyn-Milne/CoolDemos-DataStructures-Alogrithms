#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

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

		public:
			explicit Node(char character);

			[[nodiscard]] char get_character() const;
			[[nodiscard]] bool find(char c, shared_ptr<Node>& out_result) const;
			shared_ptr<Node> add(char c);
			[[nodiscard]] bool end_of_word() const;
			[[nodiscard]] size_t child_count() const;
			bool remove_node(const Node& node);

			vector<shared_ptr<Node>> nodes_;
		};

		class SearchIterator
		{
		private:
			weak_ptr<Node> node_;
			stringstream stream_;

		public:
			explicit SearchIterator(const weak_ptr<Node>& node);
			bool next(char c);
			
			string generate_string() const;
			

			vector<string> suggest_words(size_t max) const;

		private:
			void validate_node() const;
			static void reverse_string(string& str);
		};

	private:
		shared_ptr<Node> root_;

	public:
		MyTrie();
		bool add_word(const string& str);
		[[nodiscard]] bool contains_word(const string& str) const;
		bool remove_word(const string& str);

		SearchIterator search_begin();
		static SearchIterator search_end();
	private:
		static bool remove_word_dfs(const string& str, shared_ptr<Node> parent, size_t i);
	};


}
