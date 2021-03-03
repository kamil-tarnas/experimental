#include <iostream>
   
template <typename T>
T* tFactory()
{
   return new T;
}

int main()
{
   int* integer_p = tFactory<int>();

   int** foo_p = new int*;
   (*foo_p) = new int;
   int integerRef = (*integer_p);
   delete integer_p;
   std::cout << integerRef;
   std::cout << *integer_p;
   return 0;
}
