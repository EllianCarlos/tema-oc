#include <bits/stdc++.h>
#include "headers/Distance.hpp"
#include "headers/DistanceFrequency.hpp"
#include "headers/DistanceFrequencyToDistance.hpp"
#include "headers/FileParser.hpp"
#include "headers/LineToDistanceFrequency.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  // Open file and save the lines to a vector of string
  const vector<string> lineArray = FileParser::readFileLines("src/uDGP/Instance_5/Instances/distance_frequency_size5_instance1.dat");

  // Convert file lines to distance frequency objects
  vector<DistanceFrequency> distanceFrequencyList;

  for (auto it = lineArray.begin(); it != lineArray.end(); ++it)
    if (it->size() > 0)
      distanceFrequencyList.push_back(LineToDistanceFrequency::convert(*it)); 

  // Convert distance frequencys to distances
  vector<Distance> distanceList = DistanceFrequencyToDistance::convertArray(distanceFrequencyList);

  for (auto it = distanceList.begin(); it != distanceList.end(); ++it)
    cout << it->getDistance() << " ";
  cout << endl;

  // Running MD-jeep?

  // Meta Heuristic Algorithm with Distance Vector

  return 0;
}