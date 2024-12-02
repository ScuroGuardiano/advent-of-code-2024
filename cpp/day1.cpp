#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v1, v2;

  std::ifstream input("day1.txt");

  while (!input.eof())
  {
    int x, y;
    input >> x >> y;

    if (input.eof()) break;

    v1.push_back(x);
    v2.push_back(y);
  }
  input.close();

  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  int distanceSum = 0;

  for (size_t i = 0; i < v1.size(); i++)
  {
    distanceSum += std::abs(v1[i] - v2[i]);
  }

  std::cout << "Total distance is " << distanceSum << std::endl;

  // Part two
  
  int lastNumber = -1;
  size_t pos = 0;
  int lastScore = 0;
  int sum = 0;

  // Since list are sorter we can do it basically in O(n)
  for (int search : v1)
  {
    if (lastNumber == search)
    {
      sum += lastScore;
      continue;
    }

    lastScore = 0;
    for (;pos < v2.size(); pos++)
    {
      if (search == v2[pos])
      {
        lastScore += search;
      }
      if (v2[pos] > search)
      {
        break;
      }
    }

    sum += lastScore;
    lastNumber = search;
  }

  std::cout << "Similarity score is " << sum << std::endl;
}
