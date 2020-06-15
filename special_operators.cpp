#include <vector>
#include <utility>
#include <string>

// Move template to .h file?
template<typename T>
class AssocStringContainer
{
public:
	// Special functions
	AssocStringContainer();
	~AssocStringContainer();

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
T& AssocStringContainer::operator[](std::string string)
{
   for (const auto&: mStorage)
   {
      if (mStorage.first == string)
      {
         return mStorage.second;
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
	return 0;
}
