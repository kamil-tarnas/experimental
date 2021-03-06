// Shifting by 1U to divide by two - it should not matter for any contemporary comliper
// Function returns the index of searched element in the array

// https://stackoverflow.com/questions/12812656/optimized-binary-search

/* Parameters:
 * array: Non-null pointer, address of the first element in the array
 * arrayLen: The length of the array [0, UINT_MAX]
 * searchedElement: The value of searched element [0, UINT_MAX]
 * Returns: Function returns the index of searched element in the array, -1 if element is not found
 */
int BinarySearch(int* array, unsigned arrayLen, unsigned searchedElement)
{
	int pos = arrayLen >> 1U; // arrayLen / 2;

	// After targeting the middle point of the array
	// we would need to do at lest one iteration if the array is not empty
	do
	{
		if (array[pos] == searchedElement)
		{
			return pos;
		}
		else if (array[pos] > searchedElement)
		{
			pos = pos >> 1U; // pos / 2;
		}
		else if (array[pos] < searchedElement)
		{
			pos = (arrayLen + pos) >> 1U; // (arrayLen + pos) / 2;
		}
	// Need to check the zero-valued  and arrayLen-valued element of the array
	} while (pos > 0 || pos < arrayLen);

	return -1;
}
