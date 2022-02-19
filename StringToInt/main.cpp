#include <iostream>
#include "StringToInt.h"

int main()
{  
  const std::string testStr{"forty-six thousand two hundred and forty-five"};
  const auto res = string_to_int::parse_int(testStr);
  std::cout << res << '\n';
  return 0;
}
