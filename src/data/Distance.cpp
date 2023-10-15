#include "../headers/Distance.hpp"

Distance::Distance(double d) : distance(d)
{
  distance = d;
}

double Distance::getDistance()
{
  return distance;
}