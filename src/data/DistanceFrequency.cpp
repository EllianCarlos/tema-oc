#include "../headers/DistanceFrequency.hpp"

DistanceFrequency::DistanceFrequency(int freq, double d)
{
  frequency = freq;
  distance = d;
}

double DistanceFrequency::getDistance()
{
  return distance;
}

int DistanceFrequency::getFrequency()
{
  return frequency;
}
