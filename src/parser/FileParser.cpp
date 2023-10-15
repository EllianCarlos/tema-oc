#include <fstream>
#include <iostream>

#include "../headers/FileParser.hpp"

using namespace std;

string FileParser::readFile(string filename)
{
  fstream fileStream;

  fileStream.open(filename, ios::in);

  string myText;

  if (fileStream.is_open())
  {

    string newText;
    while (getline(fileStream, newText))
    {
      myText += newText;
      cout << myText;
    }

    fileStream.close();
  }
  else
  {
    cout << "File not open" << endl;
  }
  
  return myText;
}

vector<string> FileParser::readFileLines(string filename)
{
  vector<string> v;

  fstream fileStream;

  fileStream.open(filename, ios::in);

  if (fileStream.is_open())
  {

    string newText;
    while (getline(fileStream, newText))
    {
      v.push_back(newText);
    }

    fileStream.close();
  }
  else
  {
    cout << "File not open" << endl;
  }
  
  return v;
}