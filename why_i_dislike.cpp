/* http://www.mistybeach.com/articles/WhyIDontLikeCPlusPlusForLargeProjects.html
 * Write a Named Point class with three members: two floating point values for the coordinates on an X-Y plane,
 * and a name represented as a 'char *'.
 * Assume that this class will be used for some sort of wargame or simulation program that
 *  treats the world as flat and that these named points will be used to represent things like cities, battlefields, etc.
 */


#include <utility>
#include <iostream>
#include <cstddef>
#include <cstring>

class NamedPoint
{
public:
	NamedPoint() : x(0), y(0)
	{
		const char* defaultName = "Default point";
		std::size_t nameLen = sizeof(defaultName)/sizeof(defaultName[0]);
		name_m = new char[nameLen];
		std::memcpy(name_m, defaultName, nameLen);
	}
	NamedPoint(float a, float b, char* const name) : x(a), y(b)
	{
		std::size_t nameLen = 0;
		char* nameIter = name;
		while (*nameIter)
		{
			++nameLen;
			++nameIter;
		}

		//Debug
		std::cout << "nameLen is :" << nameLen << "\n";
		std::cout << "Pointer difference is :" << nameIter - name << "\n";

		name_m = new char[nameLen + 1];
		std::strcpy(name_m, name);
	}
	NamedPoint(const NamedPoint& rhs) : x(rhs.x), y(rhs.y)
	{
		std::size_t nameLen = 0;
		char* nameIter = rhs.name_m;
		while (*nameIter)
		{
			++nameLen;
			++nameIter;
		}

		name_m = new char[nameLen + 1];
		std::strcpy(name_m, rhs.name_m);
	}

	//http://www.vollmann.ch/en/blog/implementing-move-assignment-variations-in-c++.html
	NamedPoint(NamedPoint&& rhs) : x(rhs.x), y(rhs.y)
	{
		std::swap(name_m, rhs.name_m);
	}
//	NamedPoint& operator=(const NamedPoint& rhs)
//	{
//		if (&rhs != this)
//		{
//			x = rhs.x;
//			y = rhs.y;
//
//			std::size_t nameLen = 0;
//			char* nameIter = rhs.name_m;
//			while (*nameIter)
//			{
//				++nameLen;
//				++nameIter;
//			}
//
//			name_m = new char[nameLen + 1];
//			std::strcpy(name_m, rhs.name_m);
//		}
//		return *this;
//	}
	NamedPoint& operator=(NamedPoint rhs)
	{
		x = rhs.x;
		y = rhs.y;
		std::swap(name_m, rhs.name_m);
		return *this;
	}
	~NamedPoint() { delete[] name_m;}

private:
	char* name_m;
	float x;
	float y;
};


//Write r-value references...


int main()
{
	NamedPoint myPoint(5, 4, "ukulele");
	NamedPoint myThirdPoint = myPoint;
	NamedPoint mySecondPoint;
	myPoint = mySecondPoint;
	return 0;
}
