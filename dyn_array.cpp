#include <iostream>

int main()
{
   int* pointerToArray = new int[20];
   for (int i = 0; i < 20; i++)
   {
      std::cout << &pointerToArray[i] << "\n";
      std::cout << pointerToArray[i] << "\n";
   }
   return 0;
}
