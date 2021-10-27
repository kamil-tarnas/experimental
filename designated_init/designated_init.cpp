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

inline void AddSpacesToAggregate(std::string& aggregateInit)
{
	for (std::size_t charIter = 0;
		 charIter < aggregateInit.size();
		 charIter++)
	{
		if (aggregateInit.at(charIter) == ',')
		{
			charIter++;
			aggregateInit.insert(charIter, " ");
		}
	}
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

	bool isPlainVariable = false;
	bool isAggregateInit = false;

	// Accumulation is started by default
	bool accumulationStarted = true;

	// We start accumulating after the first "{"
	std::size_t posOfAccumStart = posOfOpeningBracket + 1;

	// Check for balancing the "{"
	std::size_t bracketBalance = 0;

	// Start iterating over the string from the next character
	for (std::size_t charIter = posOfOpeningBracket + 1;
		 charIter < posOfClosingBracket;
		 charIter++)
	{
		// Start accumulating characters
		// at this point is either spaces or chars that build the variable name

		// Check for balancing brackets - can be integrated with the comma check
		if (row.at(charIter) == '{')
		{
			isAggregateInit = true;

			// Change std::size_t to types that cover negative values and have a run-time check
			bracketBalance++;
		}
		else if (row.at(charIter) == '}')
		{
			// Change std::size_t to types that cover negative values and have a run-time check
			bracketBalance--;
		}

		// Need to check the bracket balance to see if it is not a aggregate initialization of member
		if (bracketBalance == 0)
		{
			if (row.at(charIter) == ',')
			{
				if (accumulationStarted == true) // Probably we always accumulate - it is a bad concept...
				{
					// The accumulation was started in the iterations before and we encountered a comma
					// extract the value

					// Need to extract the value
					std::string value = row.substr(posOfAccumStart, charIter - posOfAccumStart);

					// Remove all spaces surrounding the value
					value.erase(std::remove(value.begin(), value.end(), ' '), value.end());

					// We need to add spaces after each comma if it is an aggregate
					// TODO: No need to call that if it is not an aggregate...
					AddSpacesToAggregate(value);

					// Push back to the vector in ordered sequence
					values.push_back(value);

					// The next position is the position of next accumulation phase
					posOfAccumStart = charIter + 1;
				}
				else
				{
					accumulationStarted = true;
					posOfAccumStart = charIter + 1;
				}
			}
		}
	}
	return values;
}

int main()
{
	std::vector<std::string> tokens;
	tokens = GetValuesFromRow(singleLine);
	for (auto& vecElem: tokens)
	{
		std::cout << vecElem << std::endl;
	}
	return 0;
}


//// Need to check the bracket balance to see if it is not a aggregate initialization of member
//if (bracketBalance == 0)
//{
//	// Need to find the position of next comma
//	// TODO: or the next bracket!
//	std::size_t posOfNextComma = row.find_first_of(",", charIter);
//
//
//
//	// Need to extract the value
//	std::string value = row.substr(charIter, posOfNextComma - charIter);
//
//	// Remove all spaces surrounding the value
//	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
//
//	// Push back to the vector in ordered sequence
//	values.push_back(value);
//
//	// Advance the charIter to the position of the next comma
//	// In the next iteration we'll start from comma+1 position
//	charIter = posOfNextComma;
//
//}




// TODO: We can iterate over things or just have a sequence of call of standard lib
// TODO: Yeah, it's cool, but it does not handle the situation of "{"
// The variable can start at most from the next char after the bracket
//	std::size_t valueIter = posOfOpeningBracket + 1;
//
//	while (true) // get the end condition...
//	{
//		// TODO: Is calling find_first_of efficient here?
//		std::size_t posOfNextComma = row.find_first_of(",", valueIter);
//
//		if (posOfNextComma == std::string::npos)
//		{
//			break;
//		}
//
//		// Extract the value
//		std::string value = row.substr(valueIter, posOfNextComma - valueIter);
//
//		// Remove all spaces surrounding the value
//		value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
//
//		// Push back to the vector in ordered sequence
//		values.push_back(value);
//
//		valueIter = posOfNextComma + 1;
//	}

