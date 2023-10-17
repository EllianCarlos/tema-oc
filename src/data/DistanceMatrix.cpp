#include "../headers/DistanceMatrix.hpp"

#include <Eigen>

Distance::Distance(double d) : distance(d) { distance = d; }

double Distance::getDistance() { return distance; }