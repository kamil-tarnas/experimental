#include <vector>
#include <iostream>


// Time the implementation here...
template <class T>
void swap(T& a, T& b)
{
    T tmp(a);   // now we have two copies of a
    a = b;      // now we have two copies of b
    b = tmp;    // now we have two copies of tmp (aka a)
}


template <class T>
void move_swap(T&& a, T&& b)
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}


template <typename T>
class ManagingResource
{
public:
	ManagingResource() : resource_p(nullptr)
	{
		std::cout << "ManagingResource() called!\n";
	}
	ManagingResource(T value)
	{
		std::cout << "ManagingResource(T value) called!\n";
		resource_p = new T;
		*resource_p = value;
	}
	ManagingResource(const ManagingResource& rhs) //: resource_p(nullptr) -> not needed, because
	// only d-tors of fully constructed objects are invoked when the exception is thrown...
	{
		std::cout << "ManagingResource(const ManagingResource& rhs) called!\n";
		// Doesn't it have a large consequences in which, if the object allocates two times
		// and the d-tor is not invoked, the we would leak memory for the first allocation...
		// This could be solved by std::unique_ptr

		// Even this is important to the rule of that a class should manage only one resource
		// in such case no memory would be leaked, because a single allocation would happen
		// in every case...
		T* temp = new T;
		resource_p = temp;
		*resource_p = *rhs.resource_p;
	}
	ManagingResource(ManagingResource&& rhs) //TODO: Just steal the guts instead of rearraning ptrs...
	{
		std::cout << "ManagingResource(ManagingResource&& rhs) called!\n";
		resource_p = rhs.resource_p;
		rhs.resource_p = nullptr;
	}
	ManagingResource& operator=(const ManagingResource& rhs)
	{
		ManagingResource tmp = rhs;
		std::cout << "ManagingResource& operator=(ManagingResource rhs) called!\n";
		*this = std::move(tmp);
		return *this;
	}
	ManagingResource& operator=(ManagingResource&& rhs)
	{
		std::cout << "ManagingResource& operator=(ManagingResource&& rhs) called!\n";
		T* temp = resource_p;
		resource_p = rhs.resource_p;
		rhs.resource_p = temp;
		return *this;
	}
	~ManagingResource()
	{
		delete resource_p;
	}
private:
	T* resource_p;
};


int main()
{
	ManagingResource<int> firstResource(9);
	ManagingResource<int> secondResource(5);

	swap(firstResource, secondResource);

	std::cout << "\n\n\n";

	move_swap(ManagingResource<int>(9), ManagingResource<int>(5));

	return 0;
}
