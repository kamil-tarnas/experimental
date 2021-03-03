#include <iostream>

int main()
{
   short unsigned bitmap = (1 << 5) - 1;
   short unsigned index = 13;
   short unsigned value = (bitmap << index);
   std::cout << value << "\n";
   std::cout << sizeof(short unsigned) << "\n";
   return 0;
}
