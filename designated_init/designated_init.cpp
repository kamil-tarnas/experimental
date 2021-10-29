// Have the primitives very easily binded to this client file...

////////////////////////////////////////////////
// Major limitations (functional limitations)
// (limitations that limit the number of use cases that the program can handle)
////////////////////////////////////////////////
// 1.  Only one-dimensional arrays supported
//     reasons for the limitation: due to "golden pattern" and GetLine() getting only a single line
//     possible fix: have a var representing the array dimension  (could be read in) and do a strip-off for
//                   the brackets "{}" (single row needs to have more "{}" stripped-off (need to break the
//                   independence between iterations of GetLine() (?)
// 2. Row (one single array element) needs to be on a single line - whole element needs to occupy only one line,
//    breaking one array element on many lines (processing an element that spans across many lines) is not supported
//    reasons for the limitation: searching for opening and closing bracket (pair of "{" and corresponding "}") is
//                                done on one-line boundaries (we do search for it only in one, "active" line)
//    possible fix: need to read more than one line if closing bracket (or the bracket balance) is in separate line
//                  need to concatenate the lines (can be combined into a hybrid "row" or "entry" representing many lines)
//                  and process such entity


////////////////////////////////////////////////////
// Minor limitations (non-functional limitations)
// (limitations that do not limit the number of cases that the program can handle)
////////////////////////////////////////////////////
// 1. The comma is added to every entry (row, array element)
//    reasons for the limitation: due to single "golden pattern" for each and every row, no information of
//                                how many rows there are to process
//    possible fix: detect the last row (array element) and do not add the comma at the end


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

// For file manipulation
#include <fstream>


class LogFile
{
public:
  LogFile(const std::string& fileName);

  ~LogFile();

  LogFile(const LogFile& rhs) = delete;

  LogFile(LogFile&& rhs);

  LogFile& operator=(const LogFile& rhs) = delete;

  LogFile& operator=(LogFile&& rhs);

  // Could be auto return type, but C++14 is needed for that
  std::istream& GetLine(std::string& line);

private:
  std::ifstream fileStream_m;
};


LogFile::LogFile(const std::string& fileName)
{
  fileStream_m.open(fileName, std::ios::in);
}


LogFile::~LogFile()
{
  fileStream_m.close();
}


LogFile::LogFile(LogFile&& rhs)
{
  fileStream_m = std::move(rhs.fileStream_m);
}


LogFile& LogFile::operator=(LogFile&& rhs)
{
  fileStream_m = std::move(rhs.fileStream_m);
  return *this;
}


// Could be auto return type, but C++14 is needed for that
std::istream& LogFile::GetLine(std::string& line)
{
  return std::getline(fileStream_m, line);
}

std::string goldenPattern =
" {.someVariable = #,                                 .otherVar = #,                   .metaData = #,\n"
"  .additionalCounter = #,                            .record = #,                     .widgetNo = #,\n"
"  .tail = #,                                         .head = #\n},";

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

std::string Substitute(std::string goldenPattern, const std::vector<std::string>& values)
{
	std::size_t posIter = 0;

	for (std::size_t valueIter = 0; valueIter < values.size(); valueIter++)
	{
		// Find the "#"
		posIter = goldenPattern.find_first_of("#", posIter);

		// Erase the "#"
		goldenPattern.erase(posIter, 1);

		// Insert the value
		std::string valueToInsert = values.at(valueIter);
		goldenPattern.insert(posIter, valueToInsert);

		// Erase the excess spaces
		// TODO: Do not do it if it contains "\n" !!!!
		// TODO: Probably here is again better to just iterate ove r characters
		std::string partToCut = goldenPattern.substr(posIter + 1 + valueToInsert.size(), valueToInsert.size() );
		// See if the part contains "\n" - if so, then do not remove it...
		if (partToCut.find("\n") == std::string::npos)
		{
			goldenPattern.erase(posIter + 1 + valueToInsert.size(), valueToInsert.size() - 1);
		}
	}

	// End conditions
	// 1. find_first_of gives std::string::npos)
	// 2. no more elements in vector
	return goldenPattern;
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

	std::size_t charIter = posOfOpeningBracket + 1;
	// Start iterating over the string from the next character
	for (;
		 charIter <= posOfClosingBracket; // Changed for the case "else if (row.at(charIter) == '}') "
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

	// The last character handling...
	// TODO: Common code - can be extracted to separate subroutine
	// Need to extract the value
	std::string value = row.substr(posOfAccumStart, charIter - posOfAccumStart - 1);

	// Remove all spaces surrounding the value
	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());

	// We need to add spaces after each comma if it is an aggregate
	// TODO: No need to call that if it is not an aggregate...
	AddSpacesToAggregate(value);

	// Push back to the vector in ordered sequence
	values.push_back(value);

	return values;
}

int main()
{
//	std::vector<std::string> tokens;
//	tokens = GetValuesFromRow(singleLine);
//	for (auto& vecElem: tokens)
//	{
//		std::cout << vecElem << std::endl;
//	}
//
//	std:: cout << "##################\n\n\n";
//	std::cout << goldenPattern;
//
//	std::cout << goldenPatternTwo;
//	std::cout << Substitute(goldenPatternTwo, tokens);

	LogFile file("sample");
	std::string line;

	while (file.GetLine(line))
	{
		std::vector<std::string> tokens;
		tokens = GetValuesFromRow(line);
		std::cout << Substitute(goldenPattern, tokens);
		std::cout << std::endl;
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

