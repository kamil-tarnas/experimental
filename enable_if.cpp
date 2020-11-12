#include <iostream>

//std::is_same<decltype(sizeof(int)), std::size_t>::value
//Referring to the type and value
namespace RadixLiteral
{
   template<bool B, class T = void>
   struct enable_if {};
 
   template<class T>
   struct enable_if<true, T> {typedef T type;};

   template<bool B, class T = void>
   using enable_if_t = typename enable_if<B,T>::type;
}

int main()
{
   return 0;
}
