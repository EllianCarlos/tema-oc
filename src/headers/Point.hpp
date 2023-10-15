#ifndef __POINT
#define __POINT

class MyPoint {
public:
  double x;
  double y;
  double z;
  MyPoint(double xx, double yy, double zz);
  double GetDistance(MyPoint* p2);
  std::string Print();
};

#endif // __POINT