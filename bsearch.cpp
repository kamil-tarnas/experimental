#include <iostream>
#include <limits>

#define INVALID_VALUE std::numeric_limits<std::size_t>::max()

using std::cout;

constexpr std::size_t operator "" _z (unsigned long long size)
{
     return size;
}

template<typename Data>
size_t iterativeBinarySearch(Data array[], std::size_t size, Data value)
{
   // Use the same type to avoid conversion and truncation
   // and handle the biggest possible sizes of arrays on given platform
   size_t start = 0;
   size_t end = size - 1;

   size_t debugCounter = 0;

   while (start <= end)
   {
      debugCounter++;
      cout << debugCounter << "\n";

      size_t mid = (start + end) / 2_z; //std::size_t{2};

      if (array[mid] == value)
      {
         return mid;
      }
      else if (array[mid] > value)
      {
         end = mid - 1;
      }
      else if (array[mid] < value)
      {
         start = mid + 1;
      }
   }

   return INVALID_VALUE;
}

int main()
{
   int array[] = {1, 4, 5, 3, 3, 4};
   cout << iterativeBinarySearch(array, 6, 3) << " is the searched position of number!" << "\n";
   return 0;
}
