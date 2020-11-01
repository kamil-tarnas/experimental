#include "radixLiteral.h"
#include <iostream>

OPERATOR_LITERAL(3);
OPERATOR_LITERAL(5);

int main()
{
   std::cout << 344_b3 << "\n";
   std::cout << 5_b5 << "\n";
   return 0;
}

