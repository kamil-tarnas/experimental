// Shifting by 1U to divide by two - it should not matter for any contemporary comliper
// Function returns the index of searched element in the array

// https://stackoverflow.com/questions/12812656/optimized-binary-search

/* Parameters:
 * array: Non-null pointer, address of the first element in the array
 * arrayLen: The length of the array [0, UINT_MAX]
 * searchedElement: The value of searched element [0, UINT_MAX]
 * Returns: Function returns the index of searched element in the array, -1 if element is not found
 */
//int BinarySearch(int* array, unsigned arrayLen, unsigned searchedElement)
//{
//	int pos = arrayLen >> 1U; // arrayLen / 2;
//	int prevPos = arrayLen;
//
//	// After targeting the middle point of the array
//	// we would need to do at lest one iteration if the array is not empty
//	do
//	{
//		if (array[pos] == searchedElement)
//		{
//			return pos;
//		}
//		else if (array[pos] > searchedElement)
//		{
//			prevPos = pos;
//			pos = pos >> 1U; // pos / 2;
//		}
//		else if (array[pos] < searchedElement)
//		{
//			pos = (prevPos + pos) >> 1U; // (arrayLen + pos) / 2; //TODO: Here is the bug - we need to do pos = (posFromPrevIter + pos) / 2
//			//prevPos = pos;
//		}
//	// Need to check the zero-valued  and arrayLen-valued element of the array
//	} while (pos > 0 || pos < arrayLen);
//
//	return -1;
//}


int BinarySearch(int* array, unsigned arrayLen, unsigned searchedElement)
{
	int pos = arrayLen / 2;
	int prevPos = arrayLen;

	do
	{
		if (array[pos] == searchedElement)
		{
			return pos;
		}
		else if (array[pos] > searchedElement)
		{
			prevPos = pos;
			pos = pos / 2;
		}
		else if (array[pos] < searchedElement)
		{
			pos = (prevPos + pos) / 2;
		}

	} while (pos > 0 && pos < arrayLen);

	// could be array[0] instead of array[pos] - to not check if we went of of the
	// loop because pos >= arrayLen
	// but maybe we have the value of array[pos] in register (we also might have the array[0] though
	if (array[pos] == searchedElement)
	{
		return pos;
	}

	return -1;
}


int BinarySearchStandard(int* array, unsigned arrayLen, unsigned searchedElement)
{
	int low = 0;
	int high = arrayLen;
	int pos;

	while (low <= high)
	{
		pos = (low + high) / 2;

		if (array[pos] == searchedElement)
		{
			return pos;
		}
		else if (array[pos] > searchedElement)
		{
			// look in the low bound
			high = pos - 1;
		}
		else if (array[pos] < searchedElement)
		{
			// look in the high bound
			low = pos + 1;
		}
	}

	return -1;
}







