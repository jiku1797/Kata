#include <string>
#include <algorithm>
#include <iostream>

std::string add(std::string a, std::string b)
{
   if (a.empty())
      a = "0";
   if (b.empty())
      b = "0";

   std::string sum{};
   if (a.size() < b.size())
      std::swap(a, b);

   auto rem{ 0 };

   auto addChars = [&rem](char m, char n = '0') -> char
   {
      auto tmpSum = (m - '0') + (n - '0') + rem;
      if (tmpSum > 9)
      {
         tmpSum -= 10;
         rem = 1;
      }
      else
      {
         rem = 0;
      }
      return tmpSum + '0';
   };

   for (std::size_t i = 0; i <= a.size() - 1; ++i)
   {
      if (i <= b.size() - 1)
      {
         sum.push_back(addChars(a[a.size() - 1 - i], b[b.size() - 1 - i]));
      }
      else
      {
         sum.push_back(addChars(a[a.size() - 1 - i]));
      }
   }

   if (rem > 0)
      sum.push_back(rem + '0');

   std::reverse(sum.begin(), sum.end());
   return sum;
}

int main()
{
    std::cout << add("452", "99");
}
