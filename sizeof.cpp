#include <iostream>

int main()
{
   int* ptr_p;
   int theNumber = 6;
   int theSecondNUmber = 42;

   ptr_p = &theNumber;

   std::cout << sizeof(*ptr_p++ + 1) << std::endl; 
}
