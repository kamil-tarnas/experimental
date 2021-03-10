#ifndef OPTIMIZED_ALGOS_BUBBLE_SORT_H_
#define OPTIMIZED_ALGOS_BUBBLE_SORT_H_

#include <cstddef>

// template and develop comparable (ordering) objects (operator <)
// make a custom function and a template functio  genereated - measure the performance
// make measurements for float, int and uuser-defined class objects
// Any data-driven design possible - rearranging on data layout to get comparable results?
// (maybe if the layout of object is the same we could make a memory offsetting?
// (clearing cache?)

// Throw exceptions or any error hamndling? Everything defined by SFINAE-away?
// (but could everything be detected at compile time?)
// How to define the things to sort? Only array and its lengts? Any eements that do not have defined its sizes?
template <typename T>
void BubbleSort(T* array, std::size_t arrayLen);

#endif /* OPTIMIZED_ALGOS_BUBBLE_SORT_H_ */
