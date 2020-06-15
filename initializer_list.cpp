#include <iostream>

//?
//
//template<class T, class U>
//struct is_same : std::false_type {};
// 
// template<class T>
// struct is_same<T, T> : std::true_type {};

using std::cout;
using std::endl;

/*
template<typename T, typename U>
class IsSame
{
   public:
      IsSame(T, U);
      void GetIsSame();
   private:
      bool isSame = false;
};

template<typename T, typename T>
class IsSame
{
   public:
      IsSame(T, T);
   private:
   bool isSame = true;
};

template<typename T, typename U>
void IsSame::GetIsSame()
{
   cout << isSame << endl;
}

*/

int main()
{
   // In different standards different type is deduced (check C++11, C++14 and so on?) Josuttis?
   auto k{1}; // Deduced to be int in all standards?

   auto i = {1};

   // By template metaprograming and SFINE could get to know the type of j
   decltype(k) j = k;
   
   // Instantiate the IsSame template class and create an object
   //IsSame isItReallyTheSameType(j, i);

   //cout << isItReallyTheSameType.GetIsSame() << endl;

   std::initializer_list<int> myList = {1, 2, 3, 4, 5};

   cout << myList.size() << endl;

   auto list = {1, 3, 2, 4};
   cout << list.size() << endl;
   cout << j << endl;
   return 0;
}
