#include <fstream>
#include <iostream>

int main()
{
  std::ifstream input("day3.txt");
  char c;
  int pos = 0;
  int sum = 0;
  std::string num1 = "";
  std::string num2 = "";
  bool comma = false;
  std::string lastDoDont = "";
  bool enabled = true;
  
  char firstChars[] = { 'm', 'u', 'l', '(' };
  char doChars[] = { 'd', 'o', '(' };
  char dontChars[] = { 'd', 'o', 'n', '\'', 't', '(' };

  // yeah, I could use regex, but that's no fun
  while (input >> c)
  {
    if (c == ')')
    {
      if (!num1.empty() && !num2.empty() && enabled)
      {
        sum += std::stoi(num1) * std::stoi(num2);
      }
      else if (lastDoDont == "do(")
      {
        enabled = true;
      }
      else if (lastDoDont == "don't(")
      {
        enabled = false;
      }

      goto reset;
    }

    if (!num1.empty() && !num2.empty() && c == ')')
    {
      sum += std::stoi(num1) * std::stoi(num2);
      goto reset;
    }

    if (pos < 4 && c == firstChars[pos] && lastDoDont.empty())
    {
      pos++;
      continue;
    }
    else if (c == doChars[pos] || c == dontChars[pos])
    {
      lastDoDont += c;
      pos++;
      continue;
    }
    else if (pos < 4)
    {
      goto reset;
    }

    if (!lastDoDont.empty())
    {
      goto reset;
    }

    {
      std::string& writingNum = comma ? num2 : num1;

      if (c >= '0' && c <= '9')
      {
        writingNum += c;
        continue;
      }
      else if (c == ',' && !comma)
      {
        comma = true;
        continue;
      }
    }

  reset:
    num1.clear();
    num2.clear();
    lastDoDont.clear();
    comma = false;
    pos = 0;
  }

  std::cout << "Sum: " << sum << std::endl;
}
