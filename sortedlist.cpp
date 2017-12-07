#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "LinkedSortedList.h"


int main()
{
    srand((unsigned)time(0));
	LinkedSortedList<int> RandomList;

	for (int i = 0; i < 21; i++)
	{
		RandomList.insertSorted(rand() % 100 + 1);
	}

	RandomList.remove(RandomList.getLength());

	std::cout << "The sorted list contains: \n" << std::endl;

	for (int i = 1; i <= RandomList.getLength(); i++)
	{
		std::cout << i << ")  " << RandomList.getEntry(i) << std::endl;
	}

		return 0;
}
