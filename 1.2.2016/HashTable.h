#pragma once
#include <algorithm>
#include "List.h"
#include <stdexcept>

namespace Kolokvijum
{
	template <class T, class hash = std::hash<T>>
	class HashTable : public List<T>
	{
		friend std::ostream& operator<<(std::ostream& str, const HashTable<T> &htable)
		{
			for (int i = 0; i < htable.n; i++)
			{
				if (htable.arr[i] != nullptr)
				{
					str << *htable.arr[i];
				}
			}
			return str;
		}
	public:
		HashTable(int n) noexcept : n(n), c(0) 
		{ 
			arr = new T*[n];
			std::fill(arr, arr + n, nullptr);
		}

		void insert(T&);

		bool exists(const T&) const noexcept;
	private:
		int n;
		int c;
		T **arr;
		hash hasher;
	};

	template<class T, class hash>
	void HashTable<T, hash>::insert(T& element)
	{
		if (c < n)
		{
			if (exists(element))
			{
				*this += element;
			}
			else
			{
				int index = hasher(element) % n;
				arr[index] = &element;
				c++;
			}
		}
		else throw "Hashish table is full";

	}

	template<class T, class hash>
	inline bool HashTable<T, hash>::exists(const T& element) const noexcept
	{
		size_t index = hasher(element) % n;
		if (arr[index] && *arr[index] == element)
			return true;
		return false;
	}
}