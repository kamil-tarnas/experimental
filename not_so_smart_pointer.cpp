#include <iostream>

void YouWillGetHere()
{
	std::cout << "Yup!\n";
}

template<typename T>
class NotSoSmartPointer
{
   public:
      NotSoSmartPointer();

      // Would have some quirk - it is invoked in a loop untill the real pointer is returned and then this pointer gets dereferenced (?)
      // When overloading the structure reference then type should be a T*, because it is how it works (???)
      // So, what are the other use cases of such operator - what can be done? Calling a function work similarly...

      // It has additional, atypical constraints: It must return an object (or reference to an object)
      // that also has a pointer dereference operator,
      // or it must return a pointer that can be used to select what the pointer dereference operator arrow is pointing at

      // This would in fact do the following when called - t.operator->()->memberObject
      // So the operator is called and then it returns a pointer, which gets dereferenced and the memberObject gets accessed
      // because of the subsequent "->" operation
      // A drill down behavior, that searches for operator->() that returns a pointer

      // But, given the fact that operator->() is searched down, maybe there are some weird uses for this operator
      // (but eventually, it searches for a member variable, so this might be very limiting in fact. But on the other hand -
      // it could do something usefull a as side effect, returning the member variable as a formal requirement).
      T* operator->();
      // Any static bound checking for the pointer arithmetics? Checked bounded pointer for save operations?

};

class Treasure
{
	void (*functionPointer_p)();
};

class SecondIndirect
{
	public:
		Treasure* operator->();
};

class Indirect
{
	// Make it a friend with the NotSoSmartPointer class?
	public:
		SecondIndirect& operator->();

};
