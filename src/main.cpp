#include <bits/stdc++.h>
#include "headers/Distance.hpp"
#include "headers/DistanceFrequency.hpp"
#include "headers/DistanceFrequencyToDistance.hpp"
#include "headers/FileParser.hpp"

using namespace std;

int main(int argc, char *argv[])
{

  vector<DistanceFrequency> distanceFrequencyList;
  DistanceFrequency d1 = DistanceFrequency(5, 4.0);
  DistanceFrequency d2(1, 3.2);

  distanceFrequencyList.push_back(d1);
  distanceFrequencyList.push_back(d2);

  vector<Distance> distanceList = DistanceFrequencyToDistance::convertArray(distanceFrequencyList);

  for (auto it = distanceList.begin(); it != distanceList.end(); ++it)
    cout << it->getDistance() << " ";
  cout << endl;

  FileParser::readFile("src/uDGP/Instance_5/Instances/distance_frequency_size5_instance1.dat");

  return 0;
}