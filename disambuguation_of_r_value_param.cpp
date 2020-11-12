#include <iostream>

template<class T>
class foo
{
   public:
   void bar(T&& arg) {std::cout << "T&&\n";}
   void bar(const T& arg) {std::cout << "const T&\n";}
   // Would prefer bar(T&&) rather than bar(const T&), but won't compile in case the following overload is added:
   //void bar(T arg) {std::cout << "T\n";}
};

int main()
{
   foo<int> object;
   object.bar(5);
   return 0;
}
