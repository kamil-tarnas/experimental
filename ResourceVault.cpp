#include <string>
#include <array>

/*
 * Simulate the problem with InputParameter::InputParameter(const InputParameter&)
 * that can be found in 5b07ad7eb79f75da4805bdee453a49a26504a07d of find_layout...
 * https://github.com/kamil-tarnas/find_layout/commit/5b07ad7eb79f75da4805bdee453a49a26504a07d
 */

class Resource
{

private:
	static constexpr unsigned numberOfTreasureElements = 5;
	static unsigned numberOfFilledElements;

	static std::array<Resource, numberOfTreasureElements> resourceVault;

	Resource(std::string name, float value) : name_m(name), value_mp(nullptr)
	{
		if (numberOfFilledElements < numberOfTreasureElements)
		{
			float* valueToAssign = new float{0.0f};
			value_mp = valueToAssign;
			numberOfFilledElements++;
		}
		else
		{
			// Throw, do not create the object...
		}

		resourceVault[numberOfFilledElements] = *this; // For this the move assignment operator is needed?
	}

	std::string name_m;
	float* value_mp;
	friend int main();
};

unsigned Resource::numberOfFilledElements = 0;
std::array<Resource, Resource::numberOfTreasureElements> Resource::resourceVault =
{
	Resource("name1", 75),
	Resource("name1", 75),
	Resource("name1", 75),
	Resource("name1", 75),
	Resource("name1", 75)

};

int main()
{
	Resource myResource("Name of the res", 6.9);
	return 0;
}
