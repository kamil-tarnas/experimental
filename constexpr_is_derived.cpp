#include <typeinfo>
#include <iostream>


// Does not work with POD types
// Does not work if types are not polymorphic
template <class C, class P>
bool IsDerivedFrom()
{
	try
	{
		C* derivedClassObject;
		P* parentClassObject = dynamic_cast<P*>(derivedClassObject);
	}
	catch (std::bad_cast)
	{
		return false;
	}
	// Dynamic cast one into another - if it is then ok, if not return std::bad_cast
	// Returns true when C is derived from P
	return false; //return a helper
}


template<typename D, typename B>
class IsDerivedFromHelper
{
    class No {};
    class Yes { No no[3]; };

    static Yes Test(B*);
    static No Test(...);
public:
    enum { Is = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes) };

};


template <class C, class P>
bool IsDerivedFromExample() {
    return IsDerivedFromHelper<C, P>::Is;
}


class A
{
	int aMember;
};

class B
{
	int bMember;
};


int main()
{
	std::cout << IsDerivedFromExample<A, B>() << "\n";
	return 0;
}




