#include <iostream>
#include <memory>

int main()
{
   auto theIntegerPointer = std::make_unique<int>(5); // std::make_unique(5) will not work, why the type of the argument cannot be deducted?
   return 0;
}
