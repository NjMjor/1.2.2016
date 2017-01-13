#include "List.h"
#include <unordered_set>
#include "HashTable.h"
#include <fstream>

List<int> f(List<int> list)
{
	return list;
}

void main()
{
	Kolokvijum::HashTable<List<int>> hashtable(2);
	
	List<int> list1;
	list1 += 3;
	list1 += 1;
	list1 += 2;
	list1 += 4;

	List<int> list2 = list1;
	List<int> list3; list3 += 5; list3 += 6; list3 += 7;

	try
	{
		hashtable.insert(list1);
		hashtable.insert(list2);
		hashtable.insert(list3);
		hashtable.insert(list2);

	}
	catch (char *message)
	{
		std::cout << message;
	}

	std::ofstream file("Hashtable.txt");

	file << hashtable;
	file.close();
	system("pause");
}