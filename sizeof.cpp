#include <iostream>

struct A
{
   int b;
   int c;
   char d;
   float e;
   char f;
};

int main()
{
   int* ptr_p;
   int theNumber = 6;
   int theSecondNUmber = 42;
   A myStructA;

   std::cout << sizeof(((A*)0)->e) << std::endl;

   ptr_p = &theNumber;

   std::cout << sizeof(*ptr_p++ + 1) << std::endl; 
   std::cout << sizeof(*((int*)0)) << std::endl;
}
