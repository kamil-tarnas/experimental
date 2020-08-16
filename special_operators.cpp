#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <complex>
#include <list>

// Templatize by what?
struct FunctionObject
{
   // Only operator() overloaded overloads
   int operator()(int);
   double operator()(double);
   // Returning paired ints
   std::pair<int, int> operator()(int, int);
};

// Define only (int) overload, the rest are not used right now
int FunctionObject::operator()(int arg)
{
   return arg;
};

// Function object can take non-trivail operations as arguments? 
// But which actions cannot be passed to function as a normal parameters? 
// Is the advantage the fact that function object can hold non-static state?
// (static state can be held by a function by defining a static variable inside its body)

// The :: operator cannot be used in specyfing using declaration?
//using std::complex;
using complex = std::complex<double>;
//using std::complex;
//using Com complex<double>;
//using complex com
//typedef complex<double> complex
class Add
{
   // Implicitly private, this will be the state held by instantiated functor
   complex value;

public:
   // Add would just save the value in functor state variable
   Add(complex c)
      : value{c}
   {
   }

   Add(double re, double im)
      // What is really created here? A pair? Check this!
      : value{{re, im}}
   {
   }

   // d) Function is const (non-modifying the state of object and argument should be const to bind to r-values
   void operator()(complex& c) const
   {
      // Add the held state value to the argument that operator() is called with
	  // To the comments marked as d) - the arument cannot be const, because is modified in the body of operator()
      c += value; // Overload for l-value and r-value references? What will happen to the temporarily created Add object?
   } /// I think this should handle both r- and l- value references, for different use cases

   void operator()(complex&& c) const
   {
      c += value;
   }
};


/* COMMENTED OUT TEMPORARILY

// for_each implementation?
// Is a calable object just a type?
// Template template parameters are needed to pass the arguments?
template<typename ContainerType, typename ElementType, typename Action>
void for_each_complicated(ContainerType<ElementType>::iterator beginIter, // This is the same type, could be just typename Iter
              ContainerType<ElementType>::iterator endIter,
              Action action)
{
   while (beginIter < endIter)
   {
      action(*beginIter);
      beginIter++;
   }
}

*/

// The alternative - actually calling it with the arguments which belong to std:: drags the namespace into
// the area of template overloading because of ADL. Need to disambiguate. TODO: Other options besides introducing a namespace?
namespace experimental
{
template<typename Iter, typename Callable>
Callable for_each(Iter begin, Iter end, Callable action)
{
   while (begin != end) 
   {
      action(*begin++); // Latest fail - cannot bind non-const lvalue reference of type ‘complex&’ {aka ‘std::complex<double>&’} to an rvalue of type ‘complex’ {aka ‘std::complex<double>’}
   }
   return action; 
}
}

// Free function for adding to both std::vector and std::list
// Make the parameters optional by passing a pointer to a vec and list?
// for_each requires something callable, so a function object holdig a state is somehow
// ideal. The function of punction pointer to a function having a global 
// state is not ideal, mainly because that global state, all that comes with managing it, 
// locality principle and so on...
template<typename T>
void AddToVectorAndList(std::vector<T>& vector, std::list<T>& list, complex z)
{
   // addFunctor() creates a temporary, which is then copied as an argument to for_each?
   // If yes then it is very suboptimally done? Not really so, the argument will be then
   // used repeatedly by for_each (during loop execution)
   //
   // That's ambiguous - the ambiguity is with std::for_each, probably because of ADL
	// r-value (like Add{2,3}) needs to be taken into consideration in the template definition? (experimental::for_each?)
   experimental::for_each(vector.begin(), vector.end(), Add{2, 3}); // Constructor with initializer list is needed here?
   experimental::for_each(list.begin(), list.end(), Add{z}); // Will that create a temporary? Would it be moved?
}




// Move template to .h file?
template<typename T>
class AssocStringContainer
{
public:
	// Special functions
	AssocStringContainer() = default;
	~AssocStringContainer() = default;

	// Interface functions
   T& operator[](std::string);

private:
	std::vector<std::pair<std::string, T>> mStorage;

};

// Overload on && and & for the case if it is called with
// string that is an r-value and we can steal the guts from
// or it is called with an l-value that might/would be used
// by the called of this function
// But then you should be cautious about the usage of 
// std::move in make_pair
// Now is save as taken-by-value argument is owned by the 
// function body and does not have any dependency with
// the caller of operator[]
template<typename T>
T& AssocStringContainer<T>::operator[](std::string string)
{
   for (auto& elem: mStorage)
   {
      if (elem.first == string)
      {
         return elem.second;
      }
   }
   // Do not create a new variable? Create r-value of {string, T}
   // that will be directly fed to the push_back argument?
   // Would that auto even deduce std::pair?
   auto newElement = std::make_pair(std::move(string), 0); 
   // If the element cannot be found - push the requested string 
   // along with '0' value integer to the mStorage
   // std::move? Locality principle? push_back versus emplace_back?
   // Both are overloaded on r-value references &&
   // Perfect forwarding and piecewise-construct?
   // Uniform initialization use?
   // mStorage.push_back({string, 0});
   mStorage.push_back(std::move(newElement)); // Will it be forwarded? Ctor is not needed to be called, so no?
   // The destructor was not called is it save to return newElem?
   // Dangling reference newElem will be returned
   // Need to return the reference to the actual object in mStorage
   return mStorage.back().second;
   // The '0' needs then to be convertible to T
   // How to make it a general neutral T type value?
}

int main()
{
   AssocStringContainer<int> myAssocContainer;
   
   int numberOfItemsToAdd = 9;

   for (int element = 0; element < numberOfItemsToAdd; element++)
   {
      myAssocContainer[std::string("elem" + std::to_string(element))];
   }

   // Should deduce reference - but the ref ("&") written explicitly
   auto& referenceToElem = myAssocContainer["elem2"];
   std::cout << &referenceToElem << " | " << &myAssocContainer["elem2"] << std::endl;
   
   // Should deduce int (without a ref ("&")), because ref was not written explicitly
   auto notAreferenceToElem = myAssocContainer["elem3"];
   std::cout << &notAreferenceToElem << " | " << &myAssocContainer["elem3"] << std::endl;

   // Need to read some more about auto type deduction rules

   // Should be a copy of container element
   int copyOfElem = myAssocContainer["elem4"];
   std::cout << &copyOfElem << " | " << &myAssocContainer["elem4"] << std::endl;

   // Function object
   FunctionObject functor;
   
   int functorArgument = 42;
   int mySubsequentInteger = functor(functorArgument);
   
   std::cout << mySubsequentInteger << std::endl;

   std::vector<int> vec{1, 4, 5, 3, 6};
   std::list<int> list{2, 3, 5, 3, 4};
   complex z{1, 2};
   AddToVectorAndList(vec, list, z);

   return 0;
}
