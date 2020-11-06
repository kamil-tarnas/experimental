

#include <alloca.h>
#include <iostream>
#include <vector>

struct Base
{
    virtual ~Base() { }
    virtual int to_int() const = 0;
};

struct Integer : Base
{
    Integer(int n) : n_(n) { }
    int to_int() const { return n_; }
    int n_;
};

struct Double : Base
{
    Double(double n) : n_(n) { }
    int to_int() const { return -n_; }
    double n_;
};

inline Base* factory(double d) __attribute__((always_inline));

inline Base* factory(double d)
{
    if ((double)(int)d != d)
        return new (alloca(sizeof(Double))) Double(d);
    else
        return new (alloca(sizeof(Integer))) Integer(d);
}

int main()
{
    std::vector<Base*> numbers;
    numbers.push_back(factory(29.3));
    numbers.push_back(factory(29));
    numbers.push_back(factory(7.1));
    numbers.push_back(factory(2));
    numbers.push_back(factory(231.0));
    for (std::vector<Base*>::const_iterator i = numbers.begin();
         i != numbers.end(); ++i)
    {
        std::cout << *i << ' ' << (*i)->to_int() << '\n';
        (*i)->~Base();   // optionally / else Undefined Behaviour iff the
                         // program depends on side effects of destructor
    }
}



