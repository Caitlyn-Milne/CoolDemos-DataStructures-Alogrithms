#include "pch.h"
#include "MyTrie.h"

#include <queue>

namespace ds
{
	/*** Node ***/
	MyTrie::Node::Node(char character) : character_(character)
	{
		nodes_ = std::vector<std::shared_ptr<Node>>();
	}

	char MyTrie::Node::get_character() const
	{
		return character_;
	}

	bool MyTrie::Node::find(const char c, std::shared_ptr<Node>& out_result) const
	{
		for (auto& node_ptr : nodes_)
		{
			if (node_ptr->character_ == c)
			{
				out_result = node_ptr;
				return true;
			}
		}
		return false;
	}

	std::shared_ptr<MyTrie::Node> MyTrie::Node::add(char c)
	{
		std::shared_ptr<Node> node = std::make_shared<Node>(c);
		nodes_.push_back(node);
		return node;
	}

	bool MyTrie::Node::end_of_word() const
	{
		std::shared_ptr<Node> n;
		return find('\0', n);
	}

	size_t MyTrie::Node::child_count() const
	{
		return nodes_.size();
	}

	/*** Search ***/
	MyTrie::SearchIterator::SearchIterator(const std::weak_ptr<Node>& node) : node_(node){}

	bool MyTrie::SearchIterator::next(char c)
	{
		validate_node();
		std::shared_ptr<Node> found_node;
		const auto node = node_.lock();
		if (!node->find(c, found_node))
		{
			return false;
		}
		node_ = found_node;
		stream_ << found_node->get_character();
		return true;
	}

	std::string MyTrie::SearchIterator::generate_string() const
	{
		return stream_.str();
	}

	void MyTrie::SearchIterator::reverse_string(std::string& str)
	{
		int l = 0;
		int r = str.size() - 1;
		while(l < r)
		{
			const auto temp = str[l];
			str[l] = str[r];
			str[r] = temp;
			++l;
			--r;
		}
	}

	std::vector<std::string> MyTrie::SearchIterator::suggest_words(size_t max) const
	{
		validate_node();
		std::vector<std::shared_ptr<Node>> end_of_words;
		std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>> node_to_parent;
		//bfs
		std::queue<std::shared_ptr<Node>> queue;
		queue.push(node_.lock());
		node_to_parent[node_.lock()] = nullptr;
		while (!queue.empty() && end_of_words.size() < max)
		{
			auto node = queue.front();
			queue.pop();

			if (node->get_character() == '\0')
			{
				end_of_words.push_back(node);
				continue;
			}

			for (auto&& child : node->nodes_)
			{
				node_to_parent[child] = node;
				queue.push(child);
			}
		}
		//build result
		std::vector<std::string> result;
		std::stringstream reverse_stream;
		std::string prefix = stream_.str();
		for(const auto& end_of_word : end_of_words)
		{
			std::shared_ptr<Node> node = end_of_word;
			while (node_to_parent[node] != nullptr)
			{
				const char c = node->get_character();
				if(c != '\0')
				{
					reverse_stream << c;
				}
				node = node_to_parent[node];
			}
			//reverse word
			std::string str = reverse_stream.str();
			reverse_string(str);
			result.push_back(prefix + str);
			reverse_stream.str("");
		}
		return result;
	}

	void MyTrie::SearchIterator::validate_node() const
	{
		if (node_.expired()) 
		{
			throw std::exception("word has expired, this implementation does not support concurrency, or concurrent modification");
		}
	}


	MyTrie::SearchIterator MyTrie::search_end()
	{
		return SearchIterator(std::weak_ptr<Node>());
	}

	/*** Trie ***/

	MyTrie::MyTrie()
	{
		root_ = std::make_shared<Node>('\2');
	}

	bool MyTrie::add_word(const std::string& str)
	{
		size_t i = 0;
		std::shared_ptr<Node> node = root_;
		while (i < str.length())
		{
			std::shared_ptr<Node> found_node;
			if (node->find(str[i], found_node))
			{
				node = found_node;
			}
			else
			{
				node = node->add(str[i]);
			}
			++i;
		}
		if (node->end_of_word()) return false;
		node->add('\0');
		return true;
	}

	bool MyTrie::contains_word(const std::string& str) const
	{
		size_t i = 0;
		std::shared_ptr<Node> node = root_;
		while (i < str.length())
		{
			std::shared_ptr<Node> found_node;
			if (!node->find(str[i], found_node))
			{
				return false;
			}
			node = found_node;
			++i;
		}
		return node->end_of_word();
	}

	bool MyTrie::Node::remove_node(const Node& node)
	{
		for(auto i = nodes_.begin(); i < nodes_.end(); ++i)
		{
			if (i->get() == &node)
			{
				nodes_.erase(i);
				return true;
			}
		}
		return false;
	}

	bool MyTrie::remove_word(const std::string& str)
	{
		return remove_word_dfs(str, root_,0);
	}

	MyTrie::SearchIterator MyTrie::search_begin()
	{
		return SearchIterator(root_);
	}

	bool MyTrie::remove_word_dfs(const std::string& str, std::shared_ptr<Node> parent, size_t i)
	{
		char c;
		if (i >= str.length()) c = '\0';
		else c = str[i];

		std::shared_ptr<Node> node;
		if (!parent->find(c, node)) return false;

		if (c != '\0')
		{
			if(!remove_word_dfs(str, node, i + 1)) return false;
		}
		if (node->child_count() == 0)
		{
			parent->remove_node(*node);
		}
		return true;
	}
}
