#include <iostream>

class Parent
{
   public:
   Parent()
   {
      std::cout << "parent created!\n";
   }
};

class Derived : Parent
{
   public:
   Derived()
   {
      std::cout << "derived created!\n";
   }
};

int main()
{
   Derived d;

}
