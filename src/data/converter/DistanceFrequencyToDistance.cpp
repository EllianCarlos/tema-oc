#include <bits/stdc++.h>
#include "../../headers/DistanceFrequencyToDistance.hpp"
#include "../../headers/DistanceFrequency.hpp"
#include "../../headers/Distance.hpp"

std::vector<Distance> DistanceFrequencyToDistance::convert(DistanceFrequency d)
{
  std::vector<Distance> v;

  for (int i = 0; i < d.getFrequency(); ++i)
  {
    v.push_back(Distance(d.getDistance()));
  }

  return v;
}

std::vector<Distance> DistanceFrequencyToDistance::convertArray(std::vector<DistanceFrequency> ds)
{
  std::vector<Distance> v;

  for (auto it = ds.begin(); it != ds.end(); ++it)
    for (int i = 0; i < it->getFrequency(); ++i)
      v.push_back(Distance(it->getDistance()));

  return v;
}