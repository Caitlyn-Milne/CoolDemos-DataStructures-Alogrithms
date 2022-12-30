#pragma once
namespace ds
{
	template<typename Type>
	class IStack
	{
	public:
		virtual void push(Type&) = 0;
		virtual Type& pop() = 0;
		virtual Type& peek_last() = 0;
	};

	template<typename Type>
	class IQueue
	{
	public:
		virtual void offer(Type&) = 0;
		virtual Type& poll() = 0;
		virtual Type& peek_first() = 0;
	};

	template<typename Type>
	class IDeque : public IStack<Type>, public IQueue<Type>
	{
	public:
		virtual void add_last(Type&) = 0;
		virtual Type& remove_last() = 0;
		Type& peek_last() override = 0;

		virtual void add_first(Type&) = 0;
		virtual Type& remove_first() = 0;
		Type& peek_first() override = 0;

		void offer(Type&) final;
		Type& poll() final;
		void push(Type&) final;
		Type& pop() final;
	};

	template<typename Type>
	class MyLinkedList final : public IDeque<Type>
	{
		class Node
		{
		private:
			Type& value_;
		public:
			Node* next_ = nullptr;
			Node* previous_ = nullptr;
			Type& get_value();
			explicit Node(Type& type);
		};

	private:
		Node* head_ = nullptr;
		Node* tail_ = nullptr;
	public:
		void add_last(Type&) override;
		Type& remove_last() override;
		Type& peek_last() override;

		void add_first(Type&) override;
		Type& remove_first() override;
		Type& peek_first() override;

		~MyLinkedList();

	private:
		void validate_non_empty();
	};

	template <typename Type>
	void IDeque<Type>::offer(Type& item)
	{
		add_last(item);
	}

	template <typename Type>
	Type& IDeque<Type>::poll()
	{
		return remove_first();
	}

	template <typename Type>
	void IDeque<Type>::push(Type& item)
	{
		add_last(item);
	}

	template <typename Type>
	Type& IDeque<Type>::pop()
	{
		return remove_last();
	}

	template <typename Type>
	MyLinkedList<Type>::Node::Node(Type& type) : value_(type) {}

	template <typename Type>
	Type& MyLinkedList<Type>::Node::get_value()
	{
		return value_;
	}

	template <typename Type>
	void MyLinkedList<Type>::add_last(Type& item)
	{
		Node* node = new Node(item);
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
	Type& MyLinkedList<Type>::remove_last()
	{
		validate_non_empty();
		auto prev = tail_->previous_;
		if (prev != nullptr)
		{
			prev->next_ = nullptr;
		}
		else
		{
			head_ = nullptr;
		}
		auto result = tail_->get_value();
		delete tail_;
		tail_ = prev;
		return result;
	}

	template <typename Type>
	Type& MyLinkedList<Type>::peek_last()
	{
		validate_non_empty();
		return tail_->get_value();
	}

	template <typename Type>
	void MyLinkedList<Type>::add_first(Type& item)
	{
		Node* node = new Node(item);
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
	Type& MyLinkedList<Type>::remove_first()
	{
		validate_non_empty();
		auto next = head_->next_;
		if (next != nullptr)
		{
			next->previous_ = nullptr;
		}
		else
		{
			tail_ = nullptr;
		}
		auto result = head_->get_value();
		delete head_;
		head_ = next;
		return result;
	}

	template <typename Type>
	Type& MyLinkedList<Type>::peek_first()
	{
		validate_non_empty();
		return head_->get_value();
	}

	template <typename Type>
	MyLinkedList<Type>::~MyLinkedList()
	{
		delete head_;
		delete tail_;
	}

	template <typename Type>
	void MyLinkedList<Type>::validate_non_empty()
	{
		if (head_ == nullptr || tail_ == nullptr)
		{
			throw std::exception("data structure is empty");
		}
	}

	template class MyLinkedList<int>;
};
