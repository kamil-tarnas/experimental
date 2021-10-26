// Have the primitives very easily binded to this client file...

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

std::string singleLine;

// For the reference template to write the values
std::string stringTemplate;

inline bool ValidateRange(std::size_t start, std::size_t end)
{
	return ((start != std::string::npos) && (end != std::string::npos));
}

std::vector<std::string> GetValuesFromRow(std::string row)
{
	// RVO (?)
	std::vector<std::string> values;

	// Find the opening bracket - "{"
	std::size_t posOfOpeningBracket = row.find_first_of("{");

	// Find the closing bracket - "}" (this is the last "}", we might see many "}" in the row)
	std::size_t posOfClosingBracket = row.find_last_of("}");

	// See if the range of checking is valid
	if (ValidateRange(posOfOpeningBracket, posOfClosingBracket) == false)
	{
		// Throw or something - we do not expect this

		// Return empty vector
		return std::vector<std::string>();
	}

	// The variable can start at most from the next char after the bracket
	std::size_t valueIter = posOfOpeningBracket + 1;

	while (true) // get the end condition...
	{
		// TODO: Is calling find_first_of efficient here?
		std::size_t posOfNextComma = row.find_first_of(",", valueIter);

		if (posOfNextComma == std::string::npos)
		{
			break;
		}

		// Extract the value
		std::string value = row.substr(valueIter, posOfNextComma - valueIter);

		// Remove all spaces surrounding the value
		value.erase(std::remove(value.begin(), value.end(), ' '), value.end());

		// Push back to the vector in ordered sequence
		values.push_back(value);

		valueIter = posOfNextComma + 1;
	}

//	if (posOfOpeningBracket != std::string::npos)
//	{
//		// TODO: We can iterate over things or just have a sequence of call of standard lib
//
//		// Start iterating over the string from the next character
//		for (std::size_t charIter = posOfOpeningBracket + 1;
//			 charIter < row.size();
//			 charIter++)
//		{
//			// Start accumulating characters
//			// at this point is either spaces or chars that build the variable name
//
//		}
//
//
//		// TODO: Temp, comment-out!
//
//	}
//	else
//	{
//		// Throw or something - we do not expect this
//	}

	return values;
}

int main()
{
	return 0;
}




