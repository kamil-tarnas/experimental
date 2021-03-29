template <typename T>
class AddClass
{
public:
	T Add(T a, T b)
	{
		lastResult = a + b;
		return lastResult;
	}
	T Accum(T a, T b)
	{
		lastResult += a + b;
		return lastResult;
	}
private:
	T lastResult;
};

class AddClassB
{
public:
	int Add(int a, int b)
	{
		lasintResulint = a + b;
		return lasintResulint;
	}
	int Accum(int a, int b)
	{
		lasintResulint += a + b;
		return lasintResulint;
	}
private:
	int lasintResulint;
};

int main()
{
	AddClass<int> addObject;
	int (*function)(int, int, int);
	//function = &AddClass<int>::Add<int>(int, int);
	//function = &((void*)AddClassB::Add);
	void* myVoid_p = &((void*)AddClassB::Add);
	return 0;
}






