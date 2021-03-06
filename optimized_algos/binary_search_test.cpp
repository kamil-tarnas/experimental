#include "binary_search.h"
#include <iostream>

int main()
{
	// More tests for the algo...
	int result;
	int array[] = {1, 2, 4, 5, 6, 7, 8};
	result = BinarySearch(array, 7, 4);
	result = BinarySearch(array, 7, 8);
}
