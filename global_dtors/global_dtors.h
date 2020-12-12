#ifndef DTORS
#define DTORS

#include <iostream>

NUMERAL_SYSTEM(5);

using std::cout;

// Class for case of normal globals
class MyClass
{
   public:
   
   MyClass(int number) : mNumber(number)
   {
      cout << "Constructor of MyClass called with number" << number << "\n";
   }

   ~MyClass()
   {
      cout << "Destructor of MyClass is called, stored number is equal to" << mNumber << "\n";
   }

   private:
   int mNumber;
};


#endif
