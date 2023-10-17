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

void printSolution(vector<MyPoint> solution) {
  for (auto it = solution.begin(); it != solution.end(); ++it)
    cout << it->x << " " << it->y << " " << it->z << "\n";
  cout << endl;
}

vector<MyPoint> generateRandomValidSolution(vector<Distance> dist,
                                            int nOfPoints) {
  // TODO improve
  // TODO add validation for number of points
  vector<MyPoint> randomSolution;

  MyPoint firstPoint(0, 0, 0);
  MyPoint secondPoint(dist.at(1).getDistance(), 0, 0);
  int nOfCreatedPoints = 2;

  randomSolution.push_back(firstPoint);
  randomSolution.push_back(secondPoint);

  for (int i = 1; i < (int)dist.size() && nOfCreatedPoints < nOfPoints; ++i) {
    Distance actualDistance = dist.at(i);
    double sqrtOfDistByThree =
        sqrt(actualDistance.getDistance()) / ((double)3.0);
    double randomFactor = rand() / double(RAND_MAX);
    MyPoint otherPoint(sqrtOfDistByThree * randomFactor,
                       sqrtOfDistByThree * (1 - randomFactor),
                       sqrtOfDistByThree * (randomFactor * randomFactor));
    randomSolution.push_back(otherPoint);
    ++nOfCreatedPoints;
  }

  return randomSolution;
}

double calculateEntropyOfSolution(vector<MyPoint> *solution,
                                  vector<Distance> *distances) {
  double entropy = 0;
  for (auto firstPoint = solution->begin(); firstPoint != solution->end();
       ++firstPoint)
    for (auto secondPoint = solution->begin(); secondPoint != solution->end();
         ++secondPoint)
      if (firstPoint != secondPoint) {
        MyPoint clonedPoint = secondPoint->clone();
        entropy -= abs(firstPoint->GetDistance(&clonedPoint));
      }

  for (auto distance = distances->begin(); distance != distances->end();
       ++distance)
    entropy += abs(distance->getDistance());

  return abs(entropy);
}

vector<MyPoint> generateNeighborSolution(vector<MyPoint> *solution,
                                         vector<DistanceFrequency> *distFreq) {
  // Posible operations:
  // - swap
  // - add a very small quantity to a solution

  vector<MyPoint> neighborSolution;

  const double half = 0.50;
  const double pertubanceFactor = 0.25;

  // Generate pertubance:
  for (int i = 0; i < (int)solution->size(); ++i)
    neighborSolution.push_back(
        MyPoint(solution->at(i).x, solution->at(i).y, solution->at(i).z));

  for (int i = (int)solution->size() - 1; i > 0; --i) {
    for (int j = 0; j < 3; ++j) {
      auto randomValue = rand() / double(RAND_MAX);

      if (j == 0) {
        neighborSolution[i].x = neighborSolution[i].x *
                                (1 + pertubanceFactor * (randomValue > half));
      }

      if (j == 1) {
        neighborSolution[i].y = neighborSolution[i].y *
                                (1 + pertubanceFactor * (randomValue > half));
      }

      if (j == 2) {
        neighborSolution[i].z = neighborSolution[i].z *
                                (1 + pertubanceFactor * (randomValue > half));
      }
    }
  }

  return neighborSolution;
}

double generateInitialTemperature(double beta, double gamma, int maxIterations,
                                  double temperature, vector<MyPoint> solution,
                                  vector<Distance> *dists,
                                  vector<DistanceFrequency> *distFreq,
                                  vector<vector<MyPoint>> *acceptedSolutions) {
  bool keep = true;
  double temp = temperature;

  while (keep) {
    for (int i = 0; i < maxIterations; ++i) {
      vector<MyPoint> neighbor = generateNeighborSolution(&solution, distFreq);

      double neighborEntropy = calculateEntropyOfSolution(&neighbor, dists);
      double solutionEntropy = calculateEntropyOfSolution(&solution, dists);

      double deltaEntropy = neighborEntropy - solutionEntropy;

      if (deltaEntropy < 0) {
        acceptedSolutions->push_back(neighbor);
      } else {
        auto randomValue = rand() / double(RAND_MAX);
        if (randomValue < exp(deltaEntropy / temperature))
          acceptedSolutions->push_back(neighbor);
      }
    }
    if (acceptedSolutions->size() > gamma * maxIterations) {
      keep = false;
    } else {
      temperature = beta * temperature;
    }
  }

  return temp;
}

int main(int argc, char *argv[]) {
  // Just in case I need random
  srandom(time(NULL));

  // Open file and save the lines to a vector of string
  const vector<string> lineArray = FileParser::readFileLines(
      "uDGP/Instance_5/Instances/distance_frequency_size5_instance1.dat");

  // Convert file lines to distance frequency objects
  vector<DistanceFrequency> distanceFrequencyList;

  for (auto it = lineArray.begin(); it != lineArray.end(); ++it)
    if (it->size() > 0)
      distanceFrequencyList.push_back(LineToDistanceFrequency::convert(*it));

  // Convert distance frequencys to distances
  vector<Distance> distanceList =
      DistanceFrequencyToDistance::convertArray(distanceFrequencyList);

  // Running MD-jeep?

  // Trying to run simulated annealing

  const double alpha = 0.95;
  const double beta = 1.98;
  const double gamma = 0.95;

  // Temperatura Inicial??

  // RANDOM SOLUTION

  int nOfPoints =
      (int)(sqrt(distanceList.size() * 8 + 1.0) + 1.0) / ((double)2.0);
  vector<MyPoint> randomSolution =
      generateRandomValidSolution(distanceList, nOfPoints);

  const auto maxIterations = 20000;

  vector<MyPoint> bestSolution = randomSolution;
  long iterations = 0;
  vector<vector<MyPoint>> eliteSet;

  double temperature = generateInitialTemperature(
      beta, gamma, 99999, maxIterations, bestSolution, &distanceList,
      &distanceFrequencyList, &eliteSet);
  vector<MyPoint> workingSolution = bestSolution;

  const double tol = 1e-20;

  while (temperature > tol && iterations < maxIterations) {
    vector<MyPoint> neighbor =
        generateNeighborSolution(&workingSolution, &distanceFrequencyList);

    double neighborEntropy =
        calculateEntropyOfSolution(&neighbor, &distanceList);
    double solutionEntropy =
        calculateEntropyOfSolution(&workingSolution, &distanceList);

    double deltaEntropy = neighborEntropy - solutionEntropy;

    if (deltaEntropy < 0) {
      double bestSolutionEntropy =
          calculateEntropyOfSolution(&bestSolution, &distanceList);

      if (bestSolutionEntropy > neighborEntropy) {
        bestSolution = neighbor;
      }
    } else {
      auto randomValue = rand() / double(RAND_MAX);
      if (randomValue < exp(deltaEntropy / temperature))
        workingSolution = neighbor;
    }

    cout << "before print" << endl;

    printSolution(bestSolution);
    cout << "Current temperature: " << temperature << endl;

    temperature = temperature * alpha;
    ++iterations;
  }

  return 0;
}