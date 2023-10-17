#include <bits/stdc++.h>
#include <math.h>
#include <time.h>

#include "Eigen/Dense"

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

int main(int argc, char *argv[]) {
  // Just in case I need random
  srandom(time(NULL));

  // Open file and save the lines to a vector of string
  const vector<string> lineArray = FileParser::readFileLines(
      "uDGP/Instance_5/Instances/distance_frequency_size5_instance2.dat");

  // Convert file lines to distance frequency objects
  vector<DistanceFrequency> distanceFrequencyList;

  for (auto it = lineArray.begin(); it != lineArray.end(); ++it)
    if (it->size() > 0)
      distanceFrequencyList.push_back(LineToDistanceFrequency::convert(*it));

  // Convert distance frequencys to distances
  vector<Distance> distanceList =
      DistanceFrequencyToDistance::convertArray(distanceFrequencyList);

  int nOfPoints =
      (int)(sqrt(distanceList.size() * 8 + 1.0) + 1.0) / ((double)2.0);

  if (nOfPoints < 4) {
    cout << "Trivial solution, returning null" << endl;
  }

  // Algoritmo T?

  // 1. Achar 4 atómos base não coplanares
  // 2. Repita
  // Para cada átomo remanescente, encontre quatro átomos determinados, não
  // coplanares e vizinhos dos átomos base Encontra-se a solução x do sistema
  // linear Temos, então, que as coordenadas do átomo indeterminado xj da
  // iteração são dadas por xji = x(i+1) para i = 1,2,3 Se nenhum átomo é
  // determinado em todo o loop, pare.

  // 1. Achar átomos base não coplanares:

  // Primeiro ponto é a origem

  // creating distance matrix

  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> D(nOfPoints, nOfPoints);
  int distanceIndex = 0;
  for (int i = 0; i < nOfPoints; ++i) {
    for (int j = i; j < nOfPoints; ++j) {
      if (i == j) continue;
      D(i, j) = distanceList.at(distanceIndex).getDistance();
      D(j, i) = distanceList.at(distanceIndex).getDistance();
      distanceIndex++;
    }
  }

  cout << D << endl;

  double u2, u3, u4, v3, v4, w4;  // Definir todas essas

  u2 = D(1, 0);  // Mais ou Menos

  u3 = ((pow(D(2, 0), 2.0) - pow(D(2, 1), 2.0)) / (2.0 * (D(1, 0)))) +
       (D(1, 0) / 2.0);

  v3 = -sqrt(pow(D(2, 0), 2.0) - pow(u3, 2.0));  // Mais ou Menos

  u4 =
      (pow(D(3, 0), 2.0) - pow(D(3, 1), 2.0)) / (2.0 * D(1, 0)) + D(1, 0) / 2.0;

  v4 = (pow(D(3, 1), 2.0) - pow(D(3, 2), 2.0) - pow(u4 - u2, 2.0) +
        pow(u4 - u3, 2.0)) /
           (2.0 * v3) +
       v3 / 2.0;

  w4 = -sqrt(pow(D(3, 0), 2.0) - pow(u4, 2.0) - pow(v4, 2.0));  // Mais ou Menos

  Eigen::Vector<double, 3> x1{0, 0, 0};
  Eigen::Vector<double, 3> x2{u2, 0, 0};
  Eigen::Vector<double, 3> x3{u3, v3, 0};
  Eigen::Vector<double, 3> x4{u4, v4, w4};

  Eigen::Vector<double, 3> *solution = (Eigen::Vector<double, 3> *)malloc(
      nOfPoints * sizeof(Eigen::Vector<double, 3> *));

  solution[0] = x1;
  solution[1] = x2;
  solution[2] = x3;
  solution[3] = x4;

  Eigen::Matrix<double, 4, 3> x{
      {0, 0, 0},
      {u2, 0, 0},
      {u3, v3, 0},
      {u4, v4, w4},
  };

  // Criar Matrix A
  Eigen::Matrix<double, 3, 3> A;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      A(i, j) = (-2.0) * (x(i + 1, j) - x(0, j));
    }
  }

  for (int xi = 4; xi < nOfPoints; ++xi) {
    // Esses vetores são os pontos não coplanares bases do problema.

    // 2. Para cada ponto a ser determinado deve ser resolvido um sistema do
    // tipo Axi = b, com b e A conhecidos a partir desses vetores

    // Criar Matrix b_xi
    Eigen::Vector<double, 3> b;

    for (int i = 0; i < 3; ++i) {
      b(i) = solution[0].squaredNorm() - solution[i + 1].squaredNorm() -
             (pow(D(xi, 0), 2.0) - pow(D(xi, i + 1), 2.0));
    }

    auto xx =
        A.colPivHouseholderQr().solve(b);  // Maybe change this solution method

    solution[xi] = xx;
  }

  for (int i = 0; i < nOfPoints; ++i) {
    cout << "point [" << i << "]"
         << "\n"
         << solution[i].transpose() << endl;
  }

  // Find error by RMSD
  // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> solutionD(nOfPoints,
  //                                                                 nOfPoints);

  // for (int i = 0; i < nOfPoints; ++i) {
  //   for (int j = i; j < nOfPoints; ++j) {
  //     double rmsd = 0;
  //     for (int k = 0; k < 3; ++k) {
  //       rmsd += sqrt((1/nOfPoints) *)
  //     }
  //     solutionD(i, j) = solution[i] - solution[j];
  //     solutionD(j, i) = solutionD(i, j);
  //     distanceIndex++;
  //   }
  // }

  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> solutionDistances(
      nOfPoints, nOfPoints);
  for (int i = 0; i < nOfPoints; ++i) {
    for (int j = 0; j < nOfPoints; ++j) {
      solutionDistances(i, j) = (solution[i] - solution[j]).norm();
      distanceIndex++;
    }
  }

  cout << endl;

  cout << solutionDistances << endl;

  free(solution);

  return 0;
}