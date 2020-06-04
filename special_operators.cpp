#include <vector>
#include <utility>
#include <string>

template<typename T>
class AssocStringContainer
{
public:
	// Special functions
	AssocStringContainer();
	~AssocStringContainer();

	// Interface functions

private:
	std::vector<std::pair<std::string, T>> storage;

};

int main()
{
	return 0;
}
