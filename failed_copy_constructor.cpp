#include <iostream>

class foo
{
   public:
   foo();
   foo(foo arg);

   private:
   int goo_m;
   int* goo_mp;
};

foo::foo(foo arg)
{
   if (this != &arg)
   {
      goo_m = arg.goo_m;
      int* temp = new int;
      goo_mp = temp;
   }
}

foo::foo() : goo_m(0), goo_mp(nullptr)
{
}

int main()
{

   return 0;
}
