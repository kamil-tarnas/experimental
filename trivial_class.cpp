#include <string>

class Cust
{
private:
  std::string first;
  std::string last;
  int id;
  
public:
  Cust(const std::string& f, const std::string& l = "", int i = 0)
    : first(f), last(l), id(i)
  {
    
  }
};

int main()
{
  return 0;
}