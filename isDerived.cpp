#include <iostream>

template <class A, class B>
class isSame
{
   public:
   static const bool same = false;
};

template <class A>
class isSame<A, A>
{
   public: 
   static const bool same = true;
};

template <class A, class B>
bool isSameType()
{
   return isSame<A, B>::same;
};

int main()
{
   std::cout << isSameType<int, int>();
   return 0;
}
