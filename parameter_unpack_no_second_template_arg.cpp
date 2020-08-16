// https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c

#include <iostream>

// The variable "firstArgument" should probably be 
// named differently, as in the second call (the first recursion call)
// it would be the first parameter from parameter pack (the first
// argument from Args.., arguments).

// If only one arument is left in the unpacking it will call the below
// instantiation for T of function template
template<typename T>
void VariadicPrint(T baseArgument) 
{
   using namespace std;
   cout << baseArgument << endl;
}
   
template<typename... Args>
void VariadicPrint(Args... arguments)
{
   using namespace std;

   cout << arguments...; // should << the argument? Can it be expanded like this?
   cout << endl;
   VariadicPrint(arguments...);
}

int main()
{
   int i = 5;
   int j = 3;
   double k = 5.2;

   VariadicPrint(i, j, k);

   return 0;
}
