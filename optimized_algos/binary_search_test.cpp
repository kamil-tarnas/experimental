#include "binary_search.h"
#include <iostream>

int main()
{
	// More tests for the algo...
	int result;
	int array[] = {1, 2, 4, 5, 6, 7, 8};
	int secondArray[] = {1, 2, 4, 5, 6, 7, 8, 12, 21, 34, 45, 47};
	result = BinarySearch(secondArray, 12, 0);
	if (result != -1)
	{
		std::cout << "FAIL!\n";
	}

	result = BinarySearch(secondArray, 12, 1);
	if (result != 0)
	{
		std::cout << "FAIL!\n";
	}

	result = BinarySearch(secondArray, 12, 2);

	result = BinarySearch(array, 7, 4);
	result = BinarySearch(array, 7, 8);

	result = BinarySearch(secondArray, 12, 21);
	std::cout << result << "\n";

	if (result != 8)
	{
		std::cout << "FAIL!\n";
	}

	result = BinarySearch(secondArray, 12, 2);
	if (result != 1)
	{
		std::cout << "FAIL!\n";
	}

	result = BinarySearch(secondArray, 12, 45);
	if (result != 10)
	{
		std::cout << "FAIL!\n";
	}
}
