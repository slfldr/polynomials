#pragma once

#include <iostream>

using std::size_t;

template<typename T>
class Node
{
public:
	T value;
	Node* next;
	
	Node(T val = T(), Node* nxt = nullptr) : value(val), next(nxt) { }
};



template<typename T>
class List
{
protected:
	Node<T>* first;
	size_t size;

public:
	class Iterator
	{
		Node<T>* current;

	public:
		Iterator() : current(nullptr) {}
		Iterator(Node<T>* node) : current(node) {}
		Iterator(const Node<T>* node) : current(const_cast<Node<T>*>(node)) {}
		Iterator(const Iterator& it)
		{
			current = it.current;
		}

		Node<T>* get_current() const noexcept
		{
			return current;
		}

		Iterator& operator++()
		{
			current = current->next;

			return *this;
		}
		Iterator operator++(int)
		{
			Iterator tmp = *this;

			++(*this);

			return tmp;
		}

		T& operator*() const
		{
			return current->value;
		}
		bool operator==(const Iterator& it) const
		{
			return this->current == it.current;
		}
		bool operator!=(const Iterator& it) const
		{
			return !(*this == it);
		}
	};

	List()
	{
		first = nullptr;
		size = 0;
	}
	List(Node<T>* first_node)
	{
		first = first_node;
		size = 1;
	}
	List(const List<T>& other)
	{
		first = nullptr;
		size = 0;

		for (Iterator it = other.begin(); it != other.end(); ++it)
		{
			push_back(*it);
		}
	}
	~List()
	{
		clear();
	}

	List<T>& operator=(const List<T>& other)
	{
		if (this != &other)
		{
			clear();

			for (Iterator it = other.begin(); it != other.end(); ++it)
			{
				push_back(*it);
			}
		}

		return *this;
	}

	Node<T>* get_first() const noexcept
	{
		return first;
	}
	size_t get_size() const noexcept
	{
		return size;
	}

	typename List<T>::Iterator begin() noexcept
	{
		return Iterator(first);
	}
	typename List<T>::Iterator begin() const noexcept
	{
		return Iterator(first);
	}
	typename List<T>::Iterator end() noexcept
	{
		return Iterator();
	}
	typename List<T>::Iterator end() const noexcept
	{
		return Iterator();
	}

	void clear()
	{
		while (first != nullptr)
		{
			Node<T>* temp = first;
			first = first->next;

			delete temp;
		}

		size = 0;
	}
	void push_front(T elem)
	{
		first = new Node<T>(elem, first);

		size++;
	}
	void pop_front()
	{
		if (first == nullptr)
		{
			throw std::logic_error("List is empty");
		}

		Node<T>* temp = first;
		first = temp->next;

		delete temp;

		size--;
	}
	void insert(T elem, Node<T>* node)
	{
		if (node == nullptr)
		{
			push_front(elem);
		}
		else
		{
			node->next = new Node<T>(elem, node->next);

			size++;
		}
	}
	void erase(Node<T>* node)
	{
		if (node == nullptr || first == nullptr)
		{
			throw std::logic_error("Cannot erase from an empty list");
		}

		if (node == first)
		{
			pop_front();

			return;
		}

		Node<T>* prev = first;

		while (prev->next != node)
		{
			if (prev->next == nullptr)
			{
				throw std::logic_error("Cannot erase: node is not in the list");
			}

			prev = prev->next;
		}

		prev->next = node->next;

		delete node;

		size--;
	}

	Node<T>* get_last() const
	{
		if (first == nullptr)
		{
			return nullptr;
		}

		Node<T>* current = first;

		while (current->next != nullptr)
		{
			current = current->next;
		}

		return current;
	}

	void push_back(T elem)
	{
		insert(elem, get_last());
	}
};