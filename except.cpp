#include<iostream>
#include<stdexcept>
#include<exception>

//TODO: Whole structure of a program based on exceptions - wrap the kaywords in macros and so on?

void g()
{
   std::cout << "Hello from g()\n";
   throw std::runtime_error{"Oh, no!"};
   //try{throw std::bad_alloc;} // The try block needs to be at the save level as catch! Can it be intereleaved with some expressions?
}

void f()
{
   g();
   std::cout << "Hello from f()\n";
}

int main()
{
   try
   {
      f();
   }
   catch(const std::exception& ex)
   {
      std::cout << "We caught the exception\n" << ex.what() << "\n";
   }

   std::cout << "Hello from main()" << "\n";

   return 0;
}
