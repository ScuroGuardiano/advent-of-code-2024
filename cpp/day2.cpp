#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

bool isLineSafe(std::vector<int>& line, int omit = -1)
{
  int dir = 0;
  int last = line[omit == 0 ? 1 : 0];
  int curr;
  int start = omit == 0 ? 2 : 1;
  
  for (size_t i = start; i < line.size(); i++)
  {
    if (omit == i) continue;

    curr = line[i];
    int diff = curr - last;
    if (std::abs(diff) > 3) return false;
    if (diff == 0) return false;
    if (diff > 0 && dir == -1) return false;
    if (diff < 0 && dir == 1) return false;

    dir = diff > 0 ? 1 : -1;
    last = curr;
  }

  return true;
}

bool isLineSafeTolerateOneBad(std::vector<int>& line)
{
  if (isLineSafe(line))
  {
    return true;
  }
  
  // I have no better idea, so... XD
  for (size_t i = 0; i < line.size(); i++)
  {
    if (isLineSafe(line, i)) return true;
  }

  return false;
}

int main()
{
  std::ifstream input("day2.txt");
  int safe = 0;
  int safeWithFaultTolerance = 0;

  for (std::string line; std::getline(input, line);)
  {
    std::vector<int> v;
    std::stringstream lineStream;
    lineStream << line;
    int buff;
    while (lineStream >> buff)
    {
      v.push_back(buff);
    }

    safe += isLineSafe(v) ? 1 : 0;
    safeWithFaultTolerance += isLineSafeTolerateOneBad(v) ? 1 : 0 ;
  }

  std::cout << "Safe reports: " << safe << std::endl;
  std::cout << "Safe with fault tolerance: " << safeWithFaultTolerance << std::endl;
}
