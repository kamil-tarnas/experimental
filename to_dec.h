#ifndef TO_DEC_H
#define TO_DEC_H

// To take a char after char it needs to be done by a template parameter pack (for C++11)
// Can be done with a const char* for C++14 and beyond?
// Can be done with std::string with C++20?
// Trailing zeros before? 001010_Bin?
//
// TODO: Make it custom template, so it can be used in any base mathematical notation
// TODO: Consider different versions for different standards of C++

// Takes no arguments?
template<char... chars>
constexpr int operator""_Bin()
{

}

template<char c, char... tail>
constexpr int operator_BinUnpacker()
{
   // Assert valid input
   return // The recursive action of exponentiation the current digit
}

#endif
