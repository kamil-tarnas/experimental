//int x (a); // narrowing conversion is allowed
//int x {a}; // narrwoing conversion would yield an error
// "narrwoing conversion" is well defined in C++

struct ReferenceWrapper
{
   int& ref;
};

struct ConstWrapper
{
   ConstWrapper() : 
      //constant{5.0}
      constant{5}
   {
   }
   const int constant;
};

int main()
{
   //ReferenceWrapper foo;


   const int& referenceToInt = 200;
   
   // Would yield an error, cannot bind r-values to non-const references
   //int& nonConstRef = 200;
   ConstWrapper bar;

   return 0;
}
