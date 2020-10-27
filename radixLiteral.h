// Implementation of user-defined literals for different base number literals

// TODO: Macros for enabling specific features if compiled with different versions of C++ standard
// TODO: Iterative version (can work for C++14 and beyond)

// Use cases:
// 231_b4 -> operator""_b4<2, 3, 1>() -> 2*4^2 + 3*4^1 + 1*4^0
// 254_b6 -> operator""_b6<2, 5, 4>()
// 457_b7 -> operator""_b7<4, 5, 7>() -> should cause static_assert or some safety mechanism, not SFINAE


// Taking template parameter pack of non-type template arguments of type char
// Variadic tamplate needed probably only for C++11 standard to assign meaning for the values of digits (because of no loops, no 'if' statements, but recursion possible etc.) 
// No non-constexpr version needed, user-defined literals were introduced in C++11, the same standard as for constexpr
template<char...>
constexpr int operator"" _b3(); // TODO: Any macro magic to change the _b3 to, for example, _b6 in case of senary based system? 
                                //Need to just replace the hardcoded number in lteral suffix and implementation

template<typename Data> // TODO: Artificial constrains on the types that this template could be instantiated with?
constexpr Data pow(Data arg, int power)
{  
   // Only arithmetic types possible - how to deal with possible conversions and so on? How to deal with returning 1.0?
   // Could be done in one template or template partial specialization would be needed?
   return power == 0 ? 1.0 : arg * pow(arg, power - 1); // TODO: Swap the actual calculations with base case for more efficiency? Mark calc more likely?
}
                                
// Base case for variadic template - a helper function
template<char c>
constexpr int b3Helper() // NO FUNCTION  TO MATCH - SHOULD WE HERE ADD CHAR ARGUMENT??????????????
{
   // TODO: static_assert or other kind of check
   return (c - '0'); // TODO: Conversion from char to int is needed to give meaningful result? Or ASCII cares about it? Can this be instantiated with modified char template argment on the caller side?
}

template<char c, char... tail>
constexpr int b3Helper()
{
   // TODO: Assert or other check
   return ((c - '0') * pow(3, sizeof...(tail))) + b3Helper(tail...); // TODO: (c-'0') would get the actual int representation 
}

template<char... chars>
constexpr int operator"" _b3()
{
   return b3Helper(chars...);
}

