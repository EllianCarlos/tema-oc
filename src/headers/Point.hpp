#ifndef __POINT
#define __POINT

#include <string>

class MyPoint
{
public:
  double x;
  double y;
  double z;
  MyPoint(double x, double y, double z);
  double GetDistance(MyPoint *p2);
  std::string Print();
  MyPoint clone();
};

#endif // __POINT