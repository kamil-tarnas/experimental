#include <iostream>

#define has_expired(time_stamp, current)   ((int)((time_stamp) - (current)) >= 0)

struct timestamps
{
  unsigned current;
  unsigned start;
  unsigned end;
};

void isInRange()
{ 
   //Expected output is: 1 1 1 . 0 0 0 0 0
   const int numOfTests = 10;
   timestamps stamps[numOfTests] = {{4, 10239, 5}, {10239, 10238, 3}, {5, 1, 7}, {10, 10238, 3}, {10, 10239, 5}, {10, 1, 7}, {10, 11, 12}, {10, 10238, 3}, {10239, 10239, 5}, {5, 10238, 5}}; //last should fail!
   for (int i = 0; i < numOfTests; i++)
   {
      bool isInRange= !((stamps[i].current - stamps[i].start) <= 0 && (stamps[i].current - stamps[i].end) >= 0);
      bool isInRangeAlt = (!((stamps[i].current - stamps[i].start) <= 0) || !((stamps[i].current - stamps[i].end) >= 0)); 
      bool isInRangeOld = (stamps[i].current >= stamps[i].start && stamps[i].current <= stamps[i].end);
      bool isInRangeExp = (stamps[i].start > stamps[i].end) ? !(((int)(stamps[i].current - stamps[i].start) < 0) && ((int)(stamps[i].current - stamps[i].end) > 0)) : (stamps[i].current >= stamps[i].start && stamps[i].current <= stamps[i].end);
      //bool isInRangeExp = (stamps[i].start > stamps[i].end) ? (!((int)(stamps[i].current - stamps[i].start)) > 0 || !((int)(stamps[i].current - stamps[i].end)) < 0) : (stamps[i].current >= stamps[i].start && stamps[i].current <= stamps[i].end);
      bool isInRangeExp3 = !(stamps[i].current - stamps[i].start <= 0) && (stamps[i].current - stamps[i].end <=0);
      bool isInRangeDlMacCe = !has_expired(stamps[i].start, stamps[i].current) && has_expired(stamps[i].end, stamps[i].current);
      std::cout << " NEW:" <<  isInRange;
      std::cout << " ALT: " << isInRangeAlt;
      std::cout << " OLD: " << isInRangeOld;
      std::cout << " EXP2: " << isInRangeExp2;
      std::cout << " EXP3: " << isInRangeExp3;
      std::cout << " MACRO: " << isInRangeDlMacCe;
      std::cout << " EXP: " << isInRangeExp << "\n";
   }
}


// {4, 10239, 5} passes
// {10239, 10238, 3} passes
// {5, 1, 7} passes

int main()
{
   isInRange();
   return 0;
}

