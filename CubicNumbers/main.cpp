#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <numeric>
#include <cctype>

/* We search non-negative integer numbers, with at most 3 digits, such as the sum of the cubes of their digits is the number itself; we will call them "cubic" numbers.

153 is such a "cubic" number : 1^3 + 5^3 + 3^3 = 153
These "cubic" numbers of at most 3 digits are easy to find, even by hand, so they are "hidden" with other numbers and characters in a string.

The task is to find, or not, the "cubic" numbers in the string and then to make the sum of these "cubic" numbers found in the string, if any, and to return a string such as:

"number1 number2 (and so on if necessary) sumOfCubicNumbers Lucky"
if "cubic" numbers number1, number2, ... were found.

The numbers in the output are to be in the order in which they are encountered in the input string.

If no cubic numbers are found return the string: `"Unlucky"``.

Examples:
 - s = "aqdf&0#1xyz!22[153(777.777"
   the groups of at most 3 digits are 0 and 1 (one digit), 22 (two digits), 153, 777, 777 (3 digits)
   Only 0, 1, 153 are cubic and their sum is 154
   Return: "0 1 153 154 Lucky"

- s = "QK29a45[&erui9026315"
  the groups are 29, 45, 902, 631, 5. None is cubic.
  Return: "Unlucky"
Notes
In the string "001234" where 3 digits or more follow each other the first group to examine is "001" and the following is "234". If a packet of at most three digits has been taken, whether or not "cubic", it's over for that packet.

When a continuous string of digits exceeds 3, the string is split into groups of 3 from the left. The last grouping could have 3, 2 or 1 digits.

e.g "24172410" becomes 3 strings comprising "241", "724" and "10"

e.g "0785" becomes 2 strings comprising "078" and "5".
 *
 *
*/

namespace details
{
  std::vector<int> toDigits(int n)
  {
    std::vector<int> ret;
    while(n>0)
    {
      ret.push_back(n % 10);
      n /= 10;
    }

    return ret;
  }

  bool isCubic(const int n)
  {
    const auto digits = toDigits(n);
    const auto sumCubes = [](const int first, const int second)
    {
      return first + pow(second, 3);
    };

    const bool isCubic = (std::accumulate(std::begin(digits),
      std::end(digits), 0, sumCubes) == n);

    return isCubic;
  }

  int toDecimal(const std::vector<int> digits)
  {
    auto num{0};
    auto exp{0};
    for(auto it=digits.rbegin(); it!=digits.rend(); ++it)
    {
      num += (*it) * pow(10, exp++);
    }

    return num;
  }

  static constexpr int upperBound = 1000;
}

class Cubes
{
public:
  static void fillCubes()
  {
    for(int i=0; i<details::upperBound; ++i)
    {
      if(details::isCubic(i))
        m_cubes.insert(i);
    }
  }

  static std::string isSumOfCubes(std::string& str)
  {
    std::vector<int> tmpNum;
    std::vector<int> allNums;
    std::vector<int> cubics;
    for(auto it=str.begin(); it!=str.end(); )
    {
      if(std::isdigit(static_cast<unsigned char>(*it)))
      {
        do
        {
          tmpNum.push_back(*it);
        }
        while(++it != str.end() && std::isdigit(static_cast<unsigned char>(*it)));
      }
      else
      {
        ++it;
        continue;
      }

      if(!tmpNum.empty())
        allNums.push_back(details::toDecimal(tmpNum));

      tmpNum.clear();
    }

    if(!allNums.empty())
    {
      for(const auto num : allNums)
      {
        if(Cubes::m_cubes.find(num) != Cubes::m_cubes.end())
          cubics.push_back(num);
      }
    }

    std::string ret{};

    if(!cubics.empty())
    {
      auto sum{0};
      for(const auto cubic : cubics)
      {
        ret.append(std::to_string(cubic) + " ");
        sum += cubic;
      }
      ret.append(std::to_string(sum) + " ");
      ret.append("Lucky");
    }
    else
    {
      ret.append("Unlucky");
    }

    return ret;
  }

public:
  static std::unordered_set<int> m_cubes; // less than 1000
};

std::unordered_set<int> Cubes::m_cubes{};

int main()
{
  //std::cout << '\n' << details::isCubic(1) << '\n';
  Cubes::fillCubes();
  std::string testStr{"&z _upon 407298a --- ???ry, ww/100 I thought, 631str*ng and w===y -721&()"};
  std::cout << Cubes::isSumOfCubes(testStr) << '\n';

  return 0;
}
