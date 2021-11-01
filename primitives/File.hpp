// Open file, loop over file, do something...
// Output would be a line?
// Nah, we can do better - just have a class file, with all the client methods

// ProcessEachLine
// GetFile (or Get?)
// ProcessAllLines

// For file manipulation
#include <fstream>

class File
{
public:
  File(const std::string& fileName)
  {
    fileStream_m.open(fileName, std::ios::in);
  }

  ~File()
  {
    fileStream_m.close();
  }

  File(File&& rhs)
  {
    fileStream_m = std::move(rhs.fileStream_m);
  }

  File& operator=(File&& rhs)
  {
    fileStream_m = std::move(rhs.fileStream_m);
    return *this;
  }

  // Could be auto return type, but C++14 is needed for that
  std::istream& GetLine(std::string& line)
  {
    return std::getline(fileStream_m, line);
  }

  File(const File& rhs) = delete;

  File& operator=(const File& rhs) = delete;

private:
  std::ifstream fileStream_m;
};
