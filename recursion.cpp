#include <iostream>

// The result value will be calculated when
// winding the stack, last frame will just return
// the computed value
// In this case local variables in the consecutive
// stack frames could be optimized - the same local 
// variables could be used, even the stack frame 
// could have the same address
int MultiplyWhenAddingStackFrames(int times, int multiplier, int value)
{
   if (times > 0)
   {
      value = value * multiplier;
      return MultiplyWhenAddingStackFrames(--times, multiplier, value);
   }
   else
   {
      return value;
   }
}

// TODO: Can this be made a head type of recursion and use (utilize for computing the resulting value) return value? It can just return the non-reference of a value
// The result value would be computed when the stack unwinds
// Needs to be an addition?
// Will return a copy of "value" to its caller and modify the value thorugh the reference
int MultiplyWhenUnwindingStack(int times, int multiplier, int& value) // "value" variable needs to be a reference?
{// In case of "value" being a reference variable there is no need to return anything (the function can be void), but the value should be modified - when the stack unwinds
   if (times > 0)
   {
      MultiplyWhenUnwindingStack(--times, multiplier, value);
      value *= multiplier; // The value from all the calls instead the last one is thrown away
   }
   return value;
   // Can returning by reference solve the problem?
   // Effectively (because of one more call to the function(?) it will multiply one more time in comparison to MultiplyWhenAddingStackFrames()
}

int main()
{
   int x = 2;
   int y = 2;

   x = MultiplyWhenAddingStackFrames(3, 2, x);
   y = MultiplyWhenUnwindingStack(3, 2, y);
   
   std::cout << "x:" << x << " y:" << y << "\n";
}
