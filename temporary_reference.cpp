#include <iostream>

void incr(int&& rr) {rr++;}

void g()
{
    double ss = 1;
    int dd = 4;
    incr(ss);
    std::cout << dd << "\n";
    incr(dd);
    std::cout << dd << "\n";
}

int main()
{
	g();
}
