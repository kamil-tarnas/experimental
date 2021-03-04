#include <iostream>
#include <type_traits>
#include <utility>

int fib(int n)
{
	int fPrevPrev = 0; //f0
	int fPrev = 1; //f1

	int fn = fPrev + fPrevPrev; //f2

	for (int i = 3; i <= n; ++i)
	{
		fPrevPrev = fPrev;
		fPrev = fn;
		fn = fPrev + fPrevPrev;
	}

	return fn;
}


template<typename T> //class meets requirement or a variable meets requirements?
concept IsArthmetic = std::is_arithmetic<T>::value;

template <IsArthmetic T>
T fibRec(T n)
{
	if (n <= 1)
	{
		return n;
	}

	return fibRec(n - 2) + fibRec(n - 1);
}


// Return the index in an array
int BinarySearch(int* array, int arrayLen, int searchedElement)
{
	int pos = arrayLen / 2;

	do
	{
		if (array[pos] == searchedElement)
		{
			return pos;
		}
		else if (array[pos] > searchedElement)
		{
			pos = pos / 2;
		}
		else if (array[pos] < searchedElement)
		{
			pos = (arrayLen + pos) / 2;
		}

	} while (pos > 0 || pos < arrayLen);

	return -1;
}


// TODO: Something wrong here...
int BinarySearchRecursive(int* array, int arrayLen, int searchedElement)
{
	int pos = arrayLen / 2;

	if (array[pos] == searchedElement)
	{
		return pos;
	}
	else if (array[pos] > searchedElement)
	{
		BinarySearchRecursive(array, pos, searchedElement);
	}
	else if (array[pos] < searchedElement)
	{
		BinarySearchRecursive(&array[pos], pos, searchedElement); //TODO: Is searching wrongly...
	}
}


int FindSecondBiggest(int* array, int arrayLen)
{
	int biggestNumber = array[0];
	int secondBiggest = array[0];

	bool biggestFound = false;

	for (int i = 0; i < arrayLen; ++i)
	{
		if (array[i] > biggestNumber)
		{
			if (!biggestFound)
			{
				biggestNumber = array[i];
				biggestFound = true;
			}
			else
			{
				secondBiggest = biggestNumber;
				biggestNumber = array[i];
			}
		}
	}
	return secondBiggest;
}


void FizzBuzz(unsigned number)
{
	std::string returnedString;
	returnedString.reserve(8);

	if (number % 3 == 0)
	{
		returnedString += "Fizz";
	}
	if (number % 5 == 0)
	{
		returnedString += "Buzz";
	}

	std::cout << returnedString << "\n";
}

int main()
{
	int result;
	int array[] = {1, 2, 4, 5, 6, 7, 8};
	result = BinarySearch(array, 7, 4);
	result = BinarySearch(array, 7, 8);

	result = BinarySearchRecursive(array, 7, 8);

	std::cout << result;
	std::cout << fib(23) << "\n";
	std::cout << fibRec(23) << "\n";
	FizzBuzz(50);
	return 0;
}
