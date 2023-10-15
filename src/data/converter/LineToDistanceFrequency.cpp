#include "../../headers/LineToDistanceFrequency.hpp"

bool evaluateCondition(std::string line, int iterator, char separator);

DistanceFrequency LineToDistanceFrequency::convert(std::string line)
{
  std::string frequencyString = "";
  std::string distanceString = "";

  int i = 0;
  const char emptySpace = ' ';
  const char separator = '.';

  while (evaluateCondition(line, i, separator))
  {
    if (line.at(i) != separator && line.at(i) != emptySpace)
      frequencyString += line[i];
    i++;
  }

  i += 3;
  const char secondSeparator = '\n';

  while (evaluateCondition(line, i, secondSeparator))
  {
    if (line.at(i) != emptySpace)
      distanceString += line[i];
    i++;
  }

  return DistanceFrequency(stoi(frequencyString), atof(distanceString.c_str()));
}

bool evaluateCondition(std::string line, int iterator, char separator)
{
  const char endOfFile = '\0';
  const char endOfLine = '\n';

  return (int)line.size() > iterator && line.at(iterator) != endOfLine && line.at(iterator) != endOfFile && line.at(iterator) != separator;
}