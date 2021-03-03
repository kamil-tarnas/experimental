#include <iostream>

template <class A, class B>
constexpr bool IsSameClass();

template <class T1, class T2>
class IsSameClassHelper
{
	friend bool IsSameClass<T1, T2>();
	static constexpr bool isSame = false;
};

template <class T1>
class IsSameClassHelper<T1, T1>
{
	friend bool IsSameClass<T1, T1>();
	static constexpr bool isSame = true;
};


template <class A, class B>
constexpr bool IsSameClass()
{
	return IsSameClassHelper<A, B>::isSame;
}

int main()
{
	std::cout << IsSameClass<int, float>() << "\n";
	return 0;
}




