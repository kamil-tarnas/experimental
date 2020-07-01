constexpr int Square(int value)
{
   return value * value;
}

// The main takeaway is that is you want do not have an easy way of knowing if the object would be a constexpr and put into data segment 
// If you care about the binary size (to the extend of caring of the amount of data put into data segment of memory for constexpr objects"
// the you have no control of that (in the sense that object can be implicitly constexpr and there is not keyword for prohibiting that - there is no 'non-constexpr')
// But the con is, that even if you don't declare object as constexpr they could end up being consexpr if the requirements for creating such object are fulfilled. 
// Isn't it also the part of 'as if' rule? The compiler might decide to do stuff in compile time if it has no observable side effects in run-time?

// The other problem is that constexpr implies const, which might not be the thing that is desired. The motivation of making things constexpr might be to have a compile-time
// initialized object, which can be mutable during run time. Would this work for the thing not declared constexpr? Probably yes. The non-portable extension of Clang is 
// [[require_constant_initialization]]

// Recent knowledge - in C++20 there is constinit keyword, which does just that! It implies being initialized at compile time, but the variable can be modified during run time!


// The C++ Programming Language by Stroustrup might shed some light on the standard requirements for this topic:

//correct those lines!!!!
// const int dmv = 17; // dmv is a named constant
// int var = 17; // var is not a constant
// constexpr double max1 = 1.4∗square(dmv); // OK if square(17) is a constant expression
// constexpr double max2 = 1.4∗square(var); // error : var is not a constant expression
// const double max3 = 1.4∗square(var); // OK, may be evaluated at run time

// constexpr specified function that is used in case label? Is that possible?
//
// New thingg in C++20: constinit, consteval (immediate invocation, immediate function, that is, every call to the function must produce a compile-time constant)

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
