#include <math.h>
#include <string>

#include "../headers/Point.hpp"

MyPoint::MyPoint(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

double MyPoint::GetDistance(MyPoint *p2)
{
  return (double)sqrtf128(powf128(this->x - p2->x, 2.0) + powf128(this->y - p2->y, 2.0) + powf128(this->z - p2->z, 2.0));
}

std::string MyPoint::Print()
{
  std::string pointString;
  pointString.append(std::to_string(this->x));
  pointString.append((const char *)" ");
  pointString.append(std::to_string(this->y));
  pointString.append((const char *)" ");
  pointString.append(std::to_string(this->z));

  return pointString;
}

MyPoint MyPoint::clone()
{
  return MyPoint(this->x, this->y, this->z);
}