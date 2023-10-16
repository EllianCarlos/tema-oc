#include <bits/stdc++.h>
#include <math.h>
#include <time.h>
#include "headers/Distance.hpp"
#include "headers/DistanceFrequency.hpp"
#include "headers/DistanceFrequencyToDistance.hpp"
#include "headers/FileParser.hpp"
#include "headers/LineToDistanceFrequency.hpp"
#include "headers/Point.hpp"

using namespace std;

double distancePoints(MyPoint *p1, MyPoint *p2)
{
  return p1->GetDistance(p2);
}

vector<MyPoint> generateRandomValidSolution(vector<Distance> dist, int nOfPoints)
{
  // TODO improve
  // TODO add validation for number of points
  vector<MyPoint> randomSolution;

  MyPoint firstPoint(0, 0, 0);
  MyPoint secondPoint(0, 0, dist.at(1).getDistance());
  int nOfCreatedPoints = 2;

  randomSolution.push_back(firstPoint);
  randomSolution.push_back(secondPoint);

  for (int i = 1; i < (int)dist.size() && nOfCreatedPoints < nOfPoints; ++i)
  {
    Distance actualDistance = dist.at(i);
    double sqrtOfDistByThree = sqrt(actualDistance.getDistance()) / ((double)3.0);
    MyPoint otherPoint(sqrtOfDistByThree, sqrtOfDistByThree, sqrtOfDistByThree);
    randomSolution.push_back(otherPoint);
    ++nOfCreatedPoints;
  }

  return randomSolution;
}

vector<MyPoint> generateRandomSolution(int nOfPoints)
{
  vector<MyPoint> randomSolution;
  const long max_rand = 1000000L;
  randomSolution.push_back(MyPoint(0, 0, 0));

  for (int i = 1; i < nOfPoints; ++i)
  {
    double randomX = 3 * (random() % max_rand) / max_rand;
    double randomY = 3 * (random() % max_rand) / max_rand;
    double randomZ = 3 * (random() % max_rand) / max_rand;
    randomSolution.push_back(MyPoint(randomX, randomY, randomZ));
  }

  return randomSolution;
}

map<double, int> distanceFrequencyArrayToMap(vector<DistanceFrequency> *distFreq)
{
  map<double, int> distanceFrequencyMap;

  for (auto it = distFreq->begin(); it != distFreq->end(); ++it)
    distanceFrequencyMap.emplace(make_pair(it->getDistance(), it->getFrequency()));

  return distanceFrequencyMap;
}

double calculateEntropyOfSolution(vector<MyPoint> *solution, vector<Distance> *distances)
{
  double entropy = 0;
  for (auto firstPoint = solution->begin(); firstPoint != solution->end(); ++firstPoint)
    for (auto secondPoint = solution->begin(); secondPoint != solution->end(); ++secondPoint)
    {
      if (firstPoint != secondPoint)
      {
        MyPoint clonedPoint = secondPoint->clone();
        entropy -= firstPoint->GetDistance(&clonedPoint);
      }
    }

  for (auto distance = distances->begin(); distance != distances->end(); ++distance)
    entropy += distance->getDistance();

  return abs(entropy);
}

vector<MyPoint> generateNeighborSolution(vector<MyPoint> *solution, vector<DistanceFrequency> *distFreq)
{
  // Posible operations:
  // - swap
  // - add a very small quantity to a solution

  vector<MyPoint> neighborSolution;

  const double half = 0.50;
  const double pertubanceFactor = 0.0025;

  // Generate pertubance:
  for (int i = 0; i < (int)solution->size(); ++i)
    neighborSolution.push_back(MyPoint(solution->at(i).x, solution->at(i).y, solution->at(i).z));

  for (int i = (int)solution->size() - 1; i > 0; --i)
  {
    for (int i = 0; i < 3; ++i)
    {
      auto randomValue = rand() / double(RAND_MAX);
      
      if (i == 0)
      {
        neighborSolution[i].x = neighborSolution[i].x * (1 + pertubanceFactor * (randomValue > half));
      }

      if (i == 1)
      {
        neighborSolution[i].y = neighborSolution[i].y * (1 + pertubanceFactor * (randomValue > half));
      }

      if (i == 2)
      {
        neighborSolution[i].z = neighborSolution[i].z * (1 + pertubanceFactor * (randomValue > half));
      }
    }
  }

  return neighborSolution;
}

double generateInitialTemperature(
    double beta,
    double gamma,
    int maxIterations,
    double temperature,
    vector<MyPoint> solution,
    vector<Distance> *dists,
    vector<DistanceFrequency> *distFreq,
    vector<vector<MyPoint>> *acceptedSolutions)
{
  bool keep = true;
  double temp = temperature;

  while (keep)
  {
    for (int i = 0; i < maxIterations; ++i)
    {
      vector<MyPoint> neighbor = generateNeighborSolution(&solution, distFreq);

      double neighborEntropy = calculateEntropyOfSolution(&neighbor, dists);
      double solutionEntropy = calculateEntropyOfSolution(&solution, dists);

      double deltaEntropy = neighborEntropy - solutionEntropy;

      if (deltaEntropy < 0)
      {
        acceptedSolutions->push_back(neighbor);
      }
      else
      {
        auto randomValue = rand() / double(RAND_MAX);
        if (randomValue < exp(deltaEntropy / temperature))
          acceptedSolutions->push_back(neighbor);
      }
    }
    if (acceptedSolutions->size() > gamma * maxIterations)
    {
      keep = false;
    }
    else
    {
      temperature = beta * temperature;
    }
  }

  return temp;
}

int main(int argc, char *argv[])
{
  // Just in case I need random
  srandom(time(NULL));

  // Open file and save the lines to a vector of string
  const vector<string> lineArray = FileParser::readFileLines("uDGP/Instance_5/Instances/distance_frequency_size5_instance1.dat");

  // Convert file lines to distance frequency objects
  vector<DistanceFrequency> distanceFrequencyList;

  for (auto it = lineArray.begin(); it != lineArray.end(); ++it)
    if (it->size() > 0)
      distanceFrequencyList.push_back(LineToDistanceFrequency::convert(*it));

  // Convert distance frequencys to distances
  vector<Distance> distanceList = DistanceFrequencyToDistance::convertArray(distanceFrequencyList);

  // Running MD-jeep?

  // Trying to run simulated annealing

  const double alpha = 0.95;
  const double beta = 1.98;
  const double gamma = 0.95;

  // Temperatura Inicial??

  // RANDOM SOLUTION

  int nOfPoints = (int)(sqrt(distanceList.size()*8 + 1.0) + 1.0) / ((double)2.0);
  cout << "#Points " << nOfPoints << endl;
  vector<MyPoint> randomSolution = generateRandomValidSolution(distanceList, nOfPoints);

  const auto maxIterations = 20000000;

  vector<MyPoint> bestSolution = randomSolution;
  long iterations = 0;
  vector<vector<MyPoint>> eliteSet;
  double temperature = generateInitialTemperature(beta, gamma, 1000, maxIterations, bestSolution, &distanceList, &distanceFrequencyList, &eliteSet);
  vector<MyPoint> workingSolution = bestSolution;

  while (temperature > 0 && iterations < maxIterations)
  {
    vector<MyPoint> neighbor = generateNeighborSolution(&workingSolution, &distanceFrequencyList);

    double neighborEntropy = calculateEntropyOfSolution(&neighbor, &distanceList);
    double solutionEntropy = calculateEntropyOfSolution(&workingSolution, &distanceList);

    double deltaEntropy = neighborEntropy - solutionEntropy;

    if (deltaEntropy < 0)
    {
      double bestSolutionEntropy = calculateEntropyOfSolution(&bestSolution, &distanceList);

      if (bestSolutionEntropy > neighborEntropy)
      {
        bestSolution = neighbor;
      }
    }
    else
    {
      auto randomValue = rand() / double(RAND_MAX);
      if (randomValue < exp(deltaEntropy / temperature))
        workingSolution = neighbor;
    }
    temperature = temperature * alpha;
    ++iterations;
  }

  for (auto it = bestSolution.begin(); it != bestSolution.end(); ++it)
    cout << it->x << " " << it->y << " " << it->z << "\n";
  cout << endl;

  return 0;
}