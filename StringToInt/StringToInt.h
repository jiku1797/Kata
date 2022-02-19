#ifndef STRINGTOINT_H
#define STRINGTOINT_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
 * In this kata we want to convert a string into an integer. The strings simply represent the numbers in words.
 *
 * "one" => 1
 * "twenty" => 20
 * "two hundred forty-six" => 246
 * "seven hundred eighty-three thousand nine hundred and nineteen" => 783919
 * Additional Notes:

 * The minimum number is "zero" (inclusively)
 * The maximum number, which must be supported is 1 million (inclusively)
 * The "and" in e.g. "one hundred and twenty-four" is optional, in some cases it's present and in others it's not
 * All tested numbers are valid, you don't need to validate them
*/

namespace string_to_int
{
  std::unordered_map<std::string, int> ones
  {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
  };

  std::unordered_map<std::string, int> tens
  {
    {"ten", 10},
    {"eleven", 11},
    {"twelve", 12},
    {"thirteen", 13},
    {"fourteen", 14},
    {"fifteen", 15},
    {"sixteen", 16},
    {"seventeen", 17},
    {"eighteen", 18},
    {"nineteen", 19}
  };

  std::unordered_map<std::string, int> teens
  {
    {"twenty", 20},
    {"thirty", 30},
    {"forty", 40},
    {"fifty", 50},
    {"sixty", 60},
    {"seventy", 70},
    {"eighty", 80},
    {"ninety", 90}
  };

  void removeAnd(std::vector<std::string>& strings)
  {
    strings.erase(std::remove_if(std::begin(strings),
                  std::end(strings), [](std::string& str)
                  {
                    return str.compare("and") == 0;
                  }),
        strings.end());
  }

  void splitOnDash(const std::string& str, std::vector<std::string>& strings)
  {
    const std::string dash{"-"};
    std::size_t dashPos{0};

    if((dashPos = str.find(dash)) != std::string::npos)
    {
      strings.push_back(str.substr(0, dashPos));
      strings.push_back(str.substr(dashPos + 1));
    }
    else
    {
      strings.push_back(str);
    }
  }

  std::vector<std::string> parse(std::string number)
  {
    const std::string delim{" "};
    std::size_t pos{0};
    std::vector<std::string> ret;

    while((pos = number.find(delim)) != std::string::npos)
    {
      splitOnDash(number.substr(0, pos), ret);

      number.erase(0, pos + delim.length());
    }

    removeAnd(ret);
    splitOnDash(number, ret);

    return ret;
  }

  int translate(const std::vector<std::string>& numbers)
  {
    int tmpNum{0};
    int num{0};

    for(const auto& word : numbers)
    {
      if(auto onesIt = ones.find(word); onesIt != ones.end())
      {
        tmpNum += onesIt->second;
        continue;
      }

      if(auto tensIt = tens.find(word); tensIt != tens.end())
      {
        tmpNum += tensIt->second;
        continue;
      }

      if(auto teensIt = teens.find(word); teensIt != teens.end())
      {
        tmpNum += teensIt->second;
        continue;
      }

      if(word.compare("hundred") == 0)
      {
        tmpNum *= 100;
        continue;
      }

      if(word.compare("thousand") == 0)
      {
        tmpNum *= 1000;
        num = tmpNum;
        tmpNum = 0;
        continue;
      }

      if(word.compare("million") == 0)
      {
        tmpNum *= 1000000;
        continue;
      }
    }

    return tmpNum + num;
  }

  long parse_int(std::string number)
  {
    auto strings{parse(number)};

    return translate(strings);
  }
}

#endif // STRINGTOINT_H
