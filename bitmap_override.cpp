// The grand plan is to:
// 1. come up with an measure rate for measuring the override rate of a set of a bitmap (we are here XD)
// 2. investigate the characterisctics of that measure (and also a bit here XD)
// 3. based on that measure try to find the best subsequent bitmap of given characteristics (for example number of set bits)
//    (the backup method can be of course a brute force :( if nothing better can be found) Generation of all possible
//    bitmaps is also a permutation on a set with repeating items...
// 4. Have the bitmap - ta dam...

// Note: override rate is NOT the rate of similarity...
// Note: We can use a bruteforce method for introducing new bitmap (given the numbers of bits that are supposed to be set
//       and trying all of the combinations and checking the override rate (how to generate all the npossibilities?, n/k tuples
//       probably (?))

// MVP: Not having unfavourable and unavaiable subframes. Just a new bitmap of density

// Nominate core functions, like Core_GetOverrideRateComparision_bm
// "Core" functions need to have the only aruments and return values of fundamental types - bmSet, bm and so on...

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

// For now, a global vector
std::vector<std::pair<double, std::vector<bool>>> outputBitmaps;

using bmSet = std::vector<std::vector<bool>>;
using bm = std::vector<bool>;

// Work to be done here:
// Calculate the coverity for existing bitmaps (?)
// Iterate over existing bitmap and check the override rate of those

// The expected results:
// The optimizing task would be to minimize the rate of unfavourable entities
// Maximize the average percent of coverity defined as (A, B, C)  (AB, BC, AC) (are those variations?)
// Which one is more important? Have some synthetic measure of that?
// One more important than the other? That would make it a two-step algo, which would be simpler probably...
// Have also the unavailable subframes, that we just cannot have the permutation with 1s on that positions

// Have it in a two-step algo?
// So, firstly make the new bitmaps have the same override rate
// Then, chose the bitmaps that have the least new unfavourable subframes (?)
// Maybe the unfavourable subframes weight (the deciding factor) can be expressed as a fraction of single discrepancy?

// (this condition above seems that needs additional information or direction -
//  for example, if the rate is the same should we go with the increase in signle bitmap
//  or we should distribute it over several bitmaps) (???)


// Units to use (definitions of the units that will be used):
// How to measure the similarity across two bitmaps?
// How to measure the similarity (override rate) over n bitmap?

// Would be the similarity for n bitmap defined by those two the same?
// 1. Use the average (arithmetic (?))
//    of partial similarity defined as the similarity factor for one slot across n dimensions
// 2. Use the average (arithmetic (?))
//    of the two-bitmap similarity for all the pair that can be made out of the set (A, B, C)  (AB, BC, AC)

// Test data


// Utility to generate test data to plot "things"
// To check things that are specified on page 4 in the points defined on the right side (1. and 2.)
// yeah, so, check the "single discrepancy" influence on override rate, in the function of: firstly bm length and then
// the amount of bitmaps, and then both xD

// How "single discrepancy" influence on override rate? (1 - ((1/m)/((n^2 - n)/2))), where:
// n - the number of bitmaps in set
// m - bitmap length
// plot (1 - ((1/m)/((n^2 - n)/2)))
// (1 - ((1/m)/((n^2 - n)/2))), where n=4 m=5
// plot (1 - ((1/m)/((n^2 - n)/2))) {n,0,20} {m,0,20}
// We approach discrepancy==1 slower with increasing m than with increasing n
// We approach quicker discrepancy==1 with increasing n than m

// plot (1 - ((1/m)/((n^2 - n)/2))) {n,2,100} {m,1,100}

// Plot of reasonable values
//plot (1 - ((1/m)/((n^2 - n)/2))) {n,1,20} {m,1,20}
// Yeah, so what has bigger influence on the override rate? m or n? Plot the f and its derivatives

// d / dm dn
//d/dm dn (1 - ((1/m)/((n^2 - n)/2)))
// Does the discrepancy grow faster with n or m increasing?



// Some definitions:

// higher order bitmap - bitmap that has more "ones", "1s" set, more bits set, more "true" values as its members

// lower order bitmap - bitmap that has less "ones" set

// single discrepancy - what does it mean? We do comparisions in terms of pairs of bitmaps in the set, so
// lower order bitmap (that has less ones) would yield MORE discrepancy overall than higher order bitmap
// Do we want to define "single discrepancy" as "one" bit mismatch in ONE pair of comparisions?
// Yeah, that could be a "single" discrepancy
// That is probably not introducable into every bm set! (by changing only one bit value, even for the most optimal "order" bitmap) (???)
// Single discrepancy would "show up" the same number of times that the comparisions are made

// Number of comparisions in which a bitmap from a set of bitmaps is used is equal to n-1, where n is the number of bitmaps...

// order ambiguity - check the comment in GetOverrideRateCorrect()
// Introduce a shuffle bitmaps thing - that can print all the order of bitmaps in the set (the number of possible orders is n!)

// Can this just be implicitly converted from 0s and 1s?
std::vector<std::vector<bool>> bitmaps = // Override rate is 1 (fully overridable...)
{
		{false, true, false, true, true},
		{false, true, false, false, false},
		{false, true, false, true, false},
		{false, true, false, true, true}
};


// Can this just be implicitly converted from 0s and 1s?
std::vector<std::vector<bool>> bitmapsSingleDiscrepancy = // Override rate is 1 (fully overridable...)
{
		{false, true, false, true, true},
		{false, true, false, false, true}, //the same density of single row bitmap
		{false, true, false, true, false}, //the same density of single row bitmap
		{false, true, false, true, true}
};

std::vector<std::vector<bool>> bitmapsSingleDiscrepancyReversed = // Override rate is 1 (fully overridable...)
{
		{false, true, false, true, true},
		{false, true, false, true, false}, //the same density of single row bitmap // BUT ROWS reversed - difference to the previous one
		{false, true, false, false, true}, //the same density of single row bitmap
		{false, true, false, true, true}
};


// Stress testing
std::vector<std::vector<bool>> bitmapsLong = //m == 10
{
		{false, true, false, true, true, false, true, false, true, true},
		{false, true, false, false, true, false, true, false, true, true}, //the same density of single row bitmap
		{false, true, false, true, false, false, true, false, true, true}, //the same density of single row bitmap
		{false, true, false, true, true, false, true, false, true, true}
};



// The result would be held in std::vector<std::vector<std::vector<bool>>>

// Permutate the bitmap above
void Permute(std::vector<std::vector<bool>>& a, int l, int r, std::vector<std::vector<std::vector<bool>>>& out)
{
	if (l == r)
	{
		// Action of the permute
		out.push_back(a);
	}
	else
	{
		// Instead of swapping, just have a decision space to exhaust...
		for (int i = l; i <= r; ++i)
		{
			// Swap
			std::swap(a[l], a[i]);

			// Recursive call
			Permute(a, l + 1, r, out);

			// Backtrack
			std::swap(a[l], a[i]);
		}
	}
}



// The above seems it is the same, but need to shuffle and check...

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

// Generate random data (?)
std::vector<std::vector<bool>> bitmaps3 =
{
		{0, 1, 0, 1, 1},
		{0, 1, 0, 0, 0}
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


// TODO: Analyze the code efficiency of his solution (where moves and RVO are used)
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
	// Isn't that a hole in the definitions?
	// Could the set, depending on the sorting, have different discrepancy?
	// Counter example - a set of bms in which TWO have THE SAME density (number of bits set) but
	// depending on the sorting DIFFERENT override rate can be calculated...
	// The problem gets called "order ambigutity" and I'll check how it can be solved...
	SortByTheNumberOfSetElemDescending(bitmaps);

	// Compare starting from the second one
	// 2 compare with 1
	// 3 compare with 1 and 2 (divide the parameter by two)
	// 4 compare with 1, 2 and 3 (divide the outcome by three)
	// The number of comparisions that need to be make is ((n^2) - n) / 2
	// .w file - (n^2 - n) /2, where n=4

	double numberOfComparisions = 0;
	double coeff = 0;

	for (auto bitmapIter = bitmaps.begin() + 1; bitmapIter < bitmaps.end(); bitmapIter++)
	{
		for (auto bitmapToCompare = bitmaps.begin(); bitmapToCompare < bitmapIter; bitmapToCompare++)
		{
			double singleComparisonCoeff = GetOverrideRateComparision(*bitmapToCompare, *bitmapIter);
			// Compare the bitmap
			coeff += singleComparisonCoeff;
			numberOfComparisions++;
			//std::cout << "\n singleComparisonCoeff = " << singleComparisonCoeff << std::endl;
		}
	}
	//std::cout << "\n coeff = " << coeff << std::endl;
	//std::cout << "\n numberOfComparisons = " << numberOfComparisions << std::endl;
	return coeff / numberOfComparisions;
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

void PermuteOneBitmap(std::vector<std::vector<bool>>& a, int l, int r, std::vector<bool>& newBitmap)
{
	// We will hit this 'if' if the bitmap is permuted
	// Then (if l==r, so the bitmap is constructed) we will calculate the override rate:
	// Comparing it to the whole set
	// TODO: We do not generate unique bitmaps in such implementation
	//       need to find something fundamental pattern to restrict the decision space.
	//       The interface could be then also simplified - just passing the length of bitmap and
	//       the number of set bits (density)
	if (l == r) // I don't get this, why do we do it only in case l == r?
	{
		// Set with additional, new bitmap
		std::vector<std::vector<bool>> b = a;
		b.push_back(newBitmap);
		// Action of the permute
		auto overrideRate = GetOverrideRateCorrect(b);

		std::cout << "Bitmap is: ";
		// Print
		for (const auto& bitmapElem: newBitmap)
		{
			std::cout << bitmapElem;
		}

		// Here we have the printing of the override rates for each bitmap...
		// We can add this to, lets say a global vector (for now) and see which is the best bitmap...
		std::cout << std::endl;
		std::cout << " overrideRate of the bitmap is " << overrideRate << std::endl;

		outputBitmaps.push_back(std::make_pair(overrideRate, newBitmap));

	}
	else
	{
		// Instead of swapping, just have a decision space to exhaust...
		for (int i = l; i <= r; ++i)
		{
			// Swap
			std::swap(newBitmap[l], newBitmap[i]);

			// Recursive call
			PermuteOneBitmap(a, l + 1, r, newBitmap);

			// Backtrack
			std::swap(newBitmap[l], newBitmap[i]);
		}
	}
}

void FindOptimalOverridingBitmap(int coverity,
		                         std::vector<bool> unavailable,
								 std::vector<bool> unfavourable,
								 std::vector<std::vector<bool>> existing)
{

}


double GetDensity(const std::vector<bool>& bitmap)
{
	std::size_t numberOfSet = 0;
	for (const auto& elem: bitmap)
	{
		if (elem == true)
		{
			numberOfSet++;
		}
	}
	return numberOfSet / bitmap.size();
}


// Assumes all the bitmaps in the set are the same length
double GetDensity(const std::vector<std::vector<bool>>& bitmaps)
{
	// Have a partial handling of the coeff for each bitmap
	// TODO: What are the limits here?
	// TODO: Numeric errors here? For partial handling versus the whole in one go?
	double partialDensity = 0.0;
	for (const auto& bitmap: bitmaps)
	{
		partialDensity += GetDensity(bitmap);
	}
	return partialDensity / bitmaps.size();
}


int main()
{
//   double overrideRate = GetOverrideRate(bitmaps);
//   std::cout << "GetOverrideRate(bitmaps) = " << overrideRate << std::endl;
//   std::cout << GetOverrideRate(bitmaps2) << std::endl;


	// The GetOverrideCorrect take a set of bitmap, should that be reflected in the name?
   double overrideRateCorrect = GetOverrideRateCorrect(bitmaps);
   // Do not sort it for now...
   // TODO: Get a utility to print all struct?
   // TODO: Come up with the equation for commarisions...
   std::cout << "GetOverrideRateCorrect(bitmaps) = " << overrideRateCorrect << std::endl;

   overrideRateCorrect = GetOverrideRateCorrect(bitmaps2);

   std::cout << "GetOverrideRateCorrect(bitmaps2) = "<< overrideRateCorrect << std::endl;
   std::cout << "$$$$" << std::endl;

   overrideRateCorrect = GetOverrideRateCorrect(bitmapsSingleDiscrepancy);

   std::cout << "GetOverrideRateCorrect(bitmapsSingleDiscrepancy) = "<< overrideRateCorrect << std::endl;
   std::cout << "$$$$" << std::endl;

   overrideRateCorrect = GetOverrideRateCorrect(bitmapsSingleDiscrepancyReversed);

   std::cout << "GetOverrideRateCorrect(bitmapsSingleDiscrepancyReversed) = "<< overrideRateCorrect << std::endl;
   std::cout << "$$$$" << std::endl;

   std::cout << "########### here ############" << std::endl;

   std::vector<std::vector<std::vector<bool>>> out;
   Permute(bitmapsSingleDiscrepancy, 0, bitmapsSingleDiscrepancy.size() - 1, out);

   for (auto & bitmapSet: out)
   {
	   std::vector<double> overrideRate;
	   overrideRateCorrect = GetOverrideRateCorrect(bitmapSet);
	   overrideRate.push_back(overrideRateCorrect);

	   // Check if all the values are the same
	   if (std::equal(overrideRate.begin(), overrideRate.end(), overrideRate.begin()))
	   {
	       std::cout << "All elems are equal\n";
	   }
	   else
	   {
		   std::cout << "ERROR: elements not equal!\n";
	   }

	   std::cout << "GetOverrideRateCorrect(bitmapSet) = "<< overrideRateCorrect << std::endl;
	   std::cout << "$$$$" << std::endl;
   }


   // HERE IS TEH HEART OF THIS IMPLEMENTATION
   //bitmapsSingleDiscrepancy
   // Have a {false, true, false, true, true} m=5
   // Permute the values in the vector and check the override rate by GetOverrideRateCorrect, biggest wins
//   std::vector<bool> proposedBm = {false, true, false, true, true};
//   PermuteOneBitmap(bitmapsSingleDiscrepancy, 0, bitmapsSingleDiscrepancy.size() - 1, proposedBm);

   // We are permuting it anyway - better solution would be to have just the length and density passed
   std::vector<bool> proposedBm = {false, true, false, true, true, false, true, false, true, true};
   PermuteOneBitmap(bitmapsLong, 0, bitmapsLong.size() - 1, proposedBm);

   // Sort the output bitmaps based on the value of override rate
   std::sort(outputBitmaps.begin(), outputBitmaps.end(),
	[](std::pair<double, std::vector<bool>> a, std::pair<double, std::vector<bool>> b)
	  {return a.first > b.first;});

   double highestOverr = outputBitmaps[0].first; //Output bitmaps is the vector of all the bitmaps


   // Check if the bitmaps are the same and maybe just pick the best one...
   std::cout << "In order of bitmaps\n";
   // Loop over the bitmaps and print all the bitmaps that have the highest override rate...
   for (auto & bm: outputBitmaps)
   {
	   if (bm.first == highestOverr)
	   {
			for (const auto& elem: bm.second)
			{
				std::cout << "\033[32m" << elem;
			}
			std::cout << std::endl;
	   }
	   std::cout << "\033[39m" << bm.first << std::endl;
   }
   std::cout << std::endl;

   // Comparing the two bitmaps in regards to the "override rate"
   std::cout << GetOverrideRateComparision(bitmaps3.at(0), bitmaps3.at(1)) << std::endl;
   std::cout << GetOverrideRateComparision(bitmaps3.at(1), bitmaps3.at(0)) << std::endl;
   return 0;
}
