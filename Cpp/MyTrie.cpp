#include "pch.h"
#include "MyTrie.h"

namespace ds
{
	MyTrie::Node::Node(char character) : character_(character)
	{
		nodes_ = vector<shared_ptr<Node>>();
	}

	char MyTrie::Node::get_character() const
	{
		return character_;
	}

	bool MyTrie::Node::find(const char c, shared_ptr<Node>& out_result) const
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

	shared_ptr<MyTrie::Node> MyTrie::Node::add(char c)
	{
		shared_ptr<Node> node = make_shared<Node>(c);
		nodes_.push_back(node);
		return node;
	}

	bool MyTrie::Node::end_of_word() const
	{
		shared_ptr<Node> n;
		return find('\0', n);
	}

	size_t MyTrie::Node::child_count() const
	{
		return nodes_.size();
	}

	MyTrie::MyTrie()
	{
		root_ = make_shared<Node>('\2');
	}

	bool MyTrie::add_word(const string& str)
	{
		size_t i = 0;
		shared_ptr<Node> node = root_;
		while (i < str.length())
		{
			shared_ptr<Node> found_node;
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

	bool MyTrie::contains_word(const string& str) const
	{
		size_t i = 0;
		shared_ptr<Node> node = root_;
		while (i < str.length())
		{
			shared_ptr<Node> found_node;
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

	bool MyTrie::remove_word(const string& str)
	{
		return remove_word_dfs(str, root_,0);
	}

	bool MyTrie::remove_word_dfs(const string& str, shared_ptr<Node> parent, size_t i)
	{
		char c;
		if (i >= str.length()) c = '\0';
		else c = str[i];

		shared_ptr<Node> node;
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
