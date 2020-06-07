#include <iostream>

class MyFabulousClass
{
public:
   int firstMember;
   int secondLittleLessFabulousMember;
   char whatDoesACharDoHere;
   float notSoFabulous;
};

using std::cout;
using std::endl;

// Let's define a pointer to member for MyFabulousClass
using PointerToLessFabulousMember = char MyFabulousClass::*;

// Implicitly would be initialized to zero nevertheless
static char MyFabulousClass::* staticPointerToMember = 0;

int main()
{
   MyFabulousClass myClass;

   
   // Both pointers below point just to a member of a class - not to any specific object!
   // Not using the alias - pointing to a specific member with specified type in the MyFabulousClass class
   char MyFabulousClass::* ptrToTheCharMember = &MyFabulousClass::whatDoesACharDoHere;
   // Using the defined alias - this is also pointing just to a specific member with defined type in the class
   PointerToLessFabulousMember secondPtrToChar = &MyFabulousClass::whatDoesACharDoHere;

   // Direct access, via dot operator
   myClass.whatDoesACharDoHere = 'c';

   // Access by the pointer-to-member, done by the offset 
   myClass.*ptrToTheCharMember = 'd';

   // int castedPtrValue = static_cast<int>(staticPointerToMember);
   // But this probably would be truncated and then interpreted as char* during dereferencing? 
   // So it probably will print only the value of the first byte (char), if sizeof(int) == 4 then four such operations would be needed
   int castedPtrValue = *((char*)(&staticPointerToMember));

   // Yeah, operator precedence
   int alternativelyCastedValue = *(int*)(&staticPointerToMember);

   // Let's see the raw value of the pointer, will be equal to zero as initialized? :)
   cout << castedPtrValue << endl;

   cout << alternativelyCastedValue << endl;

   return 0;
}
