// Note: override rate is NOT the rate of similarity...

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

// Work to be done here:
// Calculate the coverity for existing bitmaps (?)
// Iterate over existing bitmap and check the override rate of those

// The expected results:
// The optimizing task would be to minimize the rate of unfavourable entities
// Maximize the average percent of coverity defined as (A, B, C)  (AB, BC, AC) (are those variations?)
// Which one is more important? Have some synthetic measure of that?
// One more important than the other? That would make it a two-step algo, which would be simpler probably...


// Units to use (definitions of the units that will be used):
// How to measure the similarity across two bitmaps?
// How to measure the similarity (override rate) over n bitmap?

// Would be the similarity for n bitmap defined by those two the same?
// 1. Use the average (arithmetic (?))
//    of partial similarity defined as the similarity factor for one slot across n dimensions
// 2. Use the average (arithmetic (?))
//    of the two-bitmap similarity for all the pair that can be made out of the set (A, B, C)  (AB, BC, AC)

// Test data

// Can this just be implicitly converted from 0s and 1s?
std::vector<std::vector<bool>> bitmaps = // Override rate is 1 (fully overridable...)
{
		{false, true, false, true, true},
		{false, true, false, false, false},
		{false, true, false, true, false},
		{false, true, false, true, true}
};

// Generate random data (?)
std::vector<std::vector<bool>> bitmaps2 =
{
		{0, 1, 0, 1, 1},
		{0, 1, 0, 0, 0},
		{0, 1, 0, 1, 0},
		{0, 1, 0, 1, 1},

		{1, 1, 1, 1, 0},
		{1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0}
};

void FindOptimalOverridingBitmap(int coverity,
		                         std::vector<bool> unavailable,
								 std::vector<bool> unfavourable,
								 std::vector<std::vector<bool>> existing);

std::size_t NumberOfSetElem(std::vector<bool>& bitmap)
{
	std::size_t numberOfSetElem = 0;

	for (const auto& elem: bitmap)
	{
		if (elem == true)
		{
			numberOfSetElem++;
		}
	}
	return numberOfSetElem;

	//return std::count(bitmap.begin(), bitmap.end(), true);
}

void SortByTheNumberOfSetElemDescending(std::vector<std::vector<bool>>& bitmaps)
{
	std::vector<std::pair<std::size_t, std::size_t>> numOfSetElem;
	std::size_t bitmapIndex = 0;

	for (const auto& elem: bitmaps)
	{
		numOfSetElem.push_back(std::make_pair(bitmapIndex, std::count(elem.begin(), elem.end(), true)));
		bitmapIndex++;
	}

	std::sort(numOfSetElem.begin(), numOfSetElem.end(),
			  [](const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b)
			  //[](auto& a, auto& b)
			  {return a.second > b.second;});

	std::vector<std::vector<bool>> bitmapsOut;
	// Resize to be the same size as the input "bitmaps"

	for (const auto& elem: numOfSetElem)
	{
		bitmapsOut.push_back(bitmaps.at(elem.first));
	}

	// Assign the output bitmap
	bitmaps = bitmapsOut;
}

double GetOverrideRateComparision(std::vector<bool>& higherOrderSetBm, std::vector<bool>& lowerOrderSetBm)
{
	// Assuming both bitmaps are the same size

	double bitmapSize = higherOrderSetBm.size();
	double numberOfSet = 0;

	for (std::size_t iter = 0; iter < higherOrderSetBm.size(); iter++)
	{
		if (higherOrderSetBm.at(iter) || !(lowerOrderSetBm.at(iter)))
		{
			numberOfSet++;
		}
	}

	return numberOfSet / bitmapSize;
}

double GetOverrideRateCorrect(std::vector<std::vector<bool>>& bitmaps)
{
	SortByTheNumberOfSetElemDescending(bitmaps);

	// Compare starting from the second one
	// 2 compare with 1
	// 3 compare with 1 and 2 (divide the parameter by two)
	// 4 compare with 1, 2 and 3 (divide the outcome by three)

	double numberOfComparisions = 0;
	double coeff = 0;

	for (auto bitmapIter = bitmaps.begin() + 1; bitmapIter < bitmaps.end(); bitmapIter++)
	{
		for (auto bitmapToCompare = bitmaps.begin(); bitmapToCompare < bitmapIter; bitmapToCompare++)
		{
			// Compare the bitmap
			coeff += GetOverrideRateComparision(*bitmapToCompare, *bitmapIter);
			numberOfComparisions++;
		}
	}
	return coeff / numberOfComparisions; // TODO: Need to correct by the "number of comparisions" factor
}

double GetOverrideRate(std::vector<std::vector<bool>> bitmaps);

double GetOverrideRate(std::vector<std::vector<bool>> bitmaps) // At which override rate policy? (Check if those are the same)
{
	std::size_t numberOfBitmaps = bitmaps.size();

	// Assuming the bitmaps are identical length
	// Lenght is the number of slots
	std::size_t lengthOfBitmap = bitmaps.at(0).size();

	// Assert that each bitmap has the same number of elements
	// TODO: Introduce a measure over different length bitmaps (?)

	// No need to initialize - it would be multiplied by slot == 0 at first iteration
	double overrideRate = 0;

	// 1. Definition - average of partial similarity
	for (std::size_t slot = 0; slot < lengthOfBitmap; slot++)
	{
		std::size_t numberOfSetSlots = 0;
		std::size_t numberOfClearSlots = 0;

		// Can make those calculations more efficient by matrixed SIMD...
		for (auto& bitmap: bitmaps)
		{
			if (bitmap.at(slot) == true)
			{
				numberOfSetSlots++;
			}
			else
			{
				numberOfClearSlots++;
			}
		}

		// If we have the number of bits set in the given slot among all the bitmaps
		// then calculate the average partial similarity
		double similaritySetSlots = (double)numberOfSetSlots / (double)numberOfBitmaps;
		double similarityClearSlots = (double)numberOfClearSlots / (double)numberOfBitmaps;

		double similarity = (similaritySetSlots > similarityClearSlots) ? similaritySetSlots : similarityClearSlots;

		// Is this the same as average? does the double type impacts it in comparison to one compound average at the end?
		// What is the difference and how can it skew the results?
		overrideRate = ((overrideRate * slot) + similarity) / (slot + 1);
	}
	// 2. Definition - average of to-bitmap comparison of all the pair that can be made out of the set (A, B, C)
	// Generate all the n-tuples from  m-sets (2-tuples of numberOfBitmaps-sets in this case) - variations without repetition
	// TODO
	return overrideRate;

}

void FindOptimalOverridingBitmap(int coverity,
		                         std::vector<bool> unavailable,
								 std::vector<bool> unfavourable,
								 std::vector<std::vector<bool>> existing)
{

}

int main()
{
   std::cout << GetOverrideRate(bitmaps) << std::endl;
   std::cout << GetOverrideRate(bitmaps2) << std::endl;

   std::cout << GetOverrideRateCorrect(bitmaps) << std::endl;
   //std::cout << GetOverrideRateCorrect(bitmaps2) << std::endl;
   std::cout << "$$$$" << std::endl;

   std::cout << GetOverrideRateComparision(bitmaps2.at(0), bitmaps2.at(1)) << std::endl;
   std::cout << GetOverrideRateComparision(bitmaps2.at(1), bitmaps2.at(0)) << std::endl;
   return 0;
}
