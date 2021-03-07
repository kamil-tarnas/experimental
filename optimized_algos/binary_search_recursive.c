#include "binary_search_recursive.h"

int BinarySearchRecursive(int* array, unsigned arrayLen, unsigned searchedElement)
{
	int pos = arrayLen / 2; // TODO: Bug - will always return 0, because eventually we are left with one-element set

	if (array[pos] == searchedElement)
	{
		return pos;
	}
	else if (array[pos] > searchedElement)
	{
		return pos - BinarySearchRecursive(array, pos, searchedElement);
	}
	else if (array[pos] < searchedElement)
	{
		// TODO: Depending on which way we recure, this might be incorrect...
		return pos + 1 + BinarySearchRecursive(&array[pos + 1], pos, searchedElement); // TODO: Pointer arithmetic so we retrieve the offset of the returned value...
	}

	return -1;
}
