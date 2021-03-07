#include "binary_search.h"
#include <iostream>

// Would be in .rodata in binary layout
// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
// A function that would take a string and construct a colored output...
//static const char* redBoldText

int main()
{
	// More tests for the algo...
	int result;
	int array[] = {1, 2, 4, 5, 6, 7, 8};
	int secondArray[] = {1, 2, 4, 5, 6, 7, 8, 12, 21, 34, 45, 47};


	result = BinarySearch(array, 7, 4);


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
	std::cout << "\033[1;31mbold red text\033[0m\n";
	std::cout << "\033[1;32mbold green text\033[0m\n";
	std::cout << "\033[0;32mnot-bold green text\033[0m\n";
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
