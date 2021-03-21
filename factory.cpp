#include <memory>
#include <iostream>


template <class T, class A1>
std::shared_ptr<T> factory_flawed(const A1& a1)
{
    return std::shared_ptr<T>(new T(a1)); // TODO: Won't work with const and non-const if T's c-tor takes
    									  // const arguments...
}


template <class T, class A1>
std::shared_ptr<T> factory(A1&& a1)
{
    return std::shared_ptr<T>(new T(std::forward<A1>(a1)));
}



class IntWrapper
{
public:
	IntWrapper(int value) : value_m(value)
	{
	}
	int GetValue()
	{
		return value_m;
	}
private:
	int value_m;
};

int main()
{
	auto myInteger = factory<IntWrapper>(3);

	std::cout << myInteger->GetValue() << "\n";

	return 0;
}
