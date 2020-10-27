#include<iostream>

class Empty
{
};

int main()
{
   Empty myEmptyClass;
   Empty array[10];

   std::cout << sizeof(Empty) << sizeof(array) << sizeof(myEmptyClass) << "\n";
   return 0;
}
