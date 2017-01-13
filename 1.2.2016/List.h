#pragma once
#include <utility>
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

template <class T>
class List
{
	struct Node
	{
		T info;
		Node *next;
		Node(const T&);
	};

	//Helper function for printing
	void print(std::ostream &str) const;

	friend std::ostream& operator<<(std::ostream &str, const List<T> &list) { list.print(str); return str; }
	
	friend struct std::hash<List<T>>;
public:
	//CONSTRUCTORS
	List() noexcept;
	List(const List<T>&) noexcept; // copy constructor
	List(List<T> &&) noexcept; //move constructor

	//Assignment operators
	List<T>& operator=(const List<T> &);
	List<T>& operator=(List<T> &&);

	List<T>& operator+=(const T&);

	bool operator==(const List<T> &other) const
	{
		if (count != other.count) return false;
		Node *head1 = head; Node *head2 = other.head;
		for (; head1; head1 = head1->next, head2 = head2->next)
		{
			if (head1->info != head2->info)
				return false;
		}
		return true;
	}

	T& operator[](int i);

	~List();

	class iterator 
	{
		Node *element;
	public:
		iterator(Node *element);

		iterator& operator++();
		iterator operator++(int);
		iterator& operator+=(int);
		T& operator*();
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;

	};

private:
	Node *head;
	int count; //number of elements

	void add(const T& info);

	//Helper functions for constructors, assignment operators and destructor
	void copy(const List<T> &);
	void move(List<T> &&);
	void del();
};

template <class T>
List<T>::iterator::iterator(typename List<T>::Node *element) : element(element) {}

template <class T>
typename List<T>::iterator::iterator& List<T>::iterator::operator++()
{
	element = element->next;
	return *this;
}

template <class T>
typename List<T>::iterator::iterator List<T>::iterator::operator++(int)
{
	iterator temp(element);
	element = element->next;
	return temp;
}

template<class T>
typename List<T>::iterator& List<T>::iterator::operator+=(int n)
{
	for (int i = 0; i < n; i++)
	{
		element = element->next;
	}
	return *this;
}

template<class T>
inline T& List<T>::iterator::operator*()
{
	return element->info;
}

template<class T>
inline bool List<T>::iterator::operator==(const typename List<T>::iterator &other) const
{
	return element == other.element;
}

template<class T>
inline bool List<T>::iterator::operator!=(const iterator & other) const
{
	return !(*this == other);
}

namespace std
{
	template<class T>
	struct hash<List<T>>
	{
		size_t operator()(const List<T> &list)const
		{
			size_t hashValue;
			typename List<T>::Node *temphead = list.head;
			while (temphead->next)
			{
				std::hash<T> hashFunction;
				hashValue = hashFunction(temphead->info) ^ hashFunction(temphead->next->info);
				temphead = temphead->next;
			}
			return hashValue;
		}
	};
	

}



template<class T>
inline List<T>::List() noexcept { head = nullptr; }

template <class T>
List<T>::List(const List<T> &other) noexcept : count(0), head(nullptr)
{
	copy(other);
}

template<class T>
inline List<T>::List(List<T> &&other) noexcept : count(0), head(nullptr)
{
	move(std::move(other));
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	del();
	copy(other);
	return *this;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>&&)
{
	del();
	move(std::move(other));
	return *this;
}

template<class T>
inline List<T>& List<T>::operator+=(const T& element)
{
	add(element);
	return *this;
}

template<class T>
T& List<T>::operator[](int i)
{
	if (i >= 0 && i < count)
	{
		List<T>::iterator it(head);
		it += i;
		return *it;
	}
	else return head->info;
}

template<class T>
inline List<T>::~List() { del(); }

template<class T>
inline void List<T>::add(const T &info)
{
	count = count + 1;
	Node *n = new Node(info);
	if (head == nullptr) { head = n; }
	else 
	{
		Node *temphead = head;
		while (temphead->next) { temphead = temphead->next; }
		temphead->next = n;
	}
}

template<class T>
inline void List<T>::copy(const List<T> &other)
{
	Node *temphead = other.head; count = 0;
	while (temphead)
	{
		add(temphead->info);
		temphead = temphead->next;
	}
}

template<class T>
inline void List<T>::move(List<T> &&other) 
{
	head = other.head;
	count = other.count;

	other.head = nullptr;
}

template<class T>
inline void List<T>::del()
{
	while (head)
	{
		Node *curr = head;
		head = head->next;
		delete curr;
	}
}

template<class T>
inline void List<T>::print(std::ostream &str) const
{
	Node *temphead = head;
	while (temphead)
	{
		str << std::setw(5) << std::left << temphead->info;
		temphead = temphead->next;
	}
}

template <class T>
List<T>::Node::Node(const T &info) : info(info), next(nullptr) {}

