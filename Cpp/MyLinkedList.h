#pragma once
#include <iostream>
#include "Interfaces.h"
namespace ds
{
	template<typename Type>
	class MyLinkedList final : public IDeque<Type>
	{
		class Node;
		using NodePtr = std::shared_ptr<Node>;
		using WeakNodePtr = std::weak_ptr<Node>;
		class Node
		{
			
		private:
			const Type& value_;
		public:
			NodePtr next_ = nullptr;
			WeakNodePtr previous_;
			const Type& get_value();
			explicit Node(const Type& type);
		};

	private:
		NodePtr head_ = nullptr;
		NodePtr tail_ = nullptr;
		int count_ = 0;
	public:
		void add_last(const Type&) override;
		const Type& remove_last() override;
		const Type& peek_last() override;

		void add_first(const Type&) override;
		const Type& remove_first() override;
		const Type& peek_first() override;

		int get_count() override;

	private:
		void validate_non_empty();
	};

	template <typename Type>
	MyLinkedList<Type>::Node::Node(const Type& type) : value_(type) {}

	template <typename Type>
	const Type& MyLinkedList<Type>::Node::get_value()
	{
		return value_;
	}

	template <typename Type>
	void MyLinkedList<Type>::add_last(const Type& item)
	{
		++count_;
		NodePtr node = std::make_shared<Node>(item);
		if (head_ == nullptr)
		{
			head_ = node;
		}
		node->previous_ = tail_;
		if (tail_ != nullptr)
		{
			tail_->next_ = node;
		}
		tail_ = node;
	}

	template <typename Type>
	const Type& MyLinkedList<Type>::remove_last()
	{
		validate_non_empty();
		--count_;
		NodePtr prev = tail_->previous_.lock();
		if (prev != nullptr)
		{
			prev->next_ = nullptr;
		}
		else
		{
			head_ = nullptr;
		}
		const Type& result = tail_->get_value();
		tail_ = prev;
		return result;
	}

	template <typename Type>
	const Type& MyLinkedList<Type>::peek_last()
	{
		validate_non_empty();
		return tail_->get_value();
	}

	template <typename Type>
	void MyLinkedList<Type>::add_first(const Type& item)
	{
		++count_;
		NodePtr node = std::make_shared<Node>(item);
		if (tail_ == nullptr)
		{
			tail_ = node;
		}
		node->next_ = head_;
		if (head_ != nullptr)
		{
			head_->previous_ = node;
		}
		head_ = node;
	}

	template <typename Type>
	const Type& MyLinkedList<Type>::remove_first()
	{
		validate_non_empty();
		--count_;
		NodePtr next = head_->next_;
		if (next != nullptr)
		{
			next->previous_.reset();
		}
		else
		{
			tail_ = nullptr;
		}
		const Type& result = head_->get_value();
		head_ = next;
		return result;
	}

	template <typename Type>
	const Type& MyLinkedList<Type>::peek_first()
	{
		validate_non_empty();
		return head_->get_value();
	}

	template <typename Type>
	int MyLinkedList<Type>::get_count()
	{
		return count_;
	}

	template <typename Type>
	void MyLinkedList<Type>::validate_non_empty()
	{
		if (head_ == nullptr || tail_ == nullptr)
		{
			throw std::exception("data structure is empty");
		}
	}
};
