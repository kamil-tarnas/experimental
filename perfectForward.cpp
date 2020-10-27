#include<iostream>
#include<utility>
#include<vector>

using std::cout;

// TODO: Make a partial template specialization in case of one parameter is given
// template<typename T> where T1 is equal to T2
template<typename T1, typename T2>
class someClass
{
   private:  
   T1 _memberOfSomeClass;
   
   public:
   template<typename U>
   someClass(U&& arg) : _memberOfSomeClass(std::forward<U>(arg))
   {
      cout << "Calling someClass ctor\n"; 
   }

   // CTAD?
   // TODO: Move to parametrize it to other type than the T type?
   std::vector<T2> _memberVector;
};

// Free function taking ref to someClass object and the vector to be assigned
template<typename T>
void set(someClass<T, T>& theClassObject, const std::vector<T>& inputVector)
{
   cout << "Calling const&\n";
   theClassObject._memberVector = inputVector;
}

// Template needed on top?
template<typename T>
void set(someClass<T, T>& theClassObject, std::vector<T>&& inputVector)
{
   cout << "Calling &&\n";
   theClassObject._memberVector = std::move(inputVector);
}

//TODO: Implement perfectSet() with the usage of std::forward

template<typename T>
std::vector<T> makeAndFillVector(const T& arg, size_t size)
{
   // RVO
   return std::vector<T>(size, arg);
}

int main()
{
   std::vector<double> vecOfDoubles{1.0, 3.0, 2.0};
   someClass<double, double> doubleObject(9.0);

   set(doubleObject, makeAndFillVector(9.0, 100));
   
   set(doubleObject, vecOfDoubles);

   // TODO: Make it workk with someClass<int> - template partial specialization
   someClass<int, int> exampleVariable(5);
   return 0;
}
