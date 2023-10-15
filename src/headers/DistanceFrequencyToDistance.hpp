#ifndef __DISTANCE_FREQUENCY_TO_DISTANCE
#define __DISTANCE_FREQUENCY_TO_DISTANCE

#include "DistanceFrequency.hpp"
#include "Distance.hpp"

class DistanceFrequencyToDistance
{
public:
  static std::vector<Distance> convert(DistanceFrequency);
  static std::vector<Distance> convertArray(std::vector<DistanceFrequency>);
};

#endif // __DISTANCE_FREQUENCY_TO_DISTANCE
