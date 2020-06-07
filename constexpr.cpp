constexpr int Square(int value)
{
   return value * value;
}

int main()
{
   // Probably will be initialized during compile time and put into data segment of memory even without the constexpr specifier
   int mySquaredValue = Square(10);

   // What about this case?
   int wouldItBe = 5;

   // Here, a complier might see that the value of 'wouldItBe' is immediately overwritten, would be also implicitly constexpr?
   wouldItBe = Square(10);

   // Here, for the argument of Square() a run-time automatic variable value is used (although its known during compilation)
   // Would the compliler make it implicitly constexpr? Even thought Square() is called with an l-value argument
   wouldItBe = Square(wouldItBe);

   return 0;

   // Can it be checked by 'g++ constexpr.cpp -o constexpr -std=c++17 && size constexpr'?
}
