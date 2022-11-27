#include <string>
#include <iostream>
#include <format>

bool isPalindrome(const unsigned int val)
{
   const auto strNum{ std::to_string(val) };
   const auto length{ strNum.size() };
   for (std::size_t i{ 0 }; i < length / 2; ++i)
   {
      if (strNum[i] != strNum[length - 1 - i])
         return false;
   }
   return true;
}

unsigned int nextPal(const unsigned int val)
{
   for (auto i{ val + 1 }; ; ++i)
   {
      if (isPalindrome(i))
         return i;
   }
}

int main()
{
   const auto start{11u};
   std::cout << 
      std::format("The next palindrome number after {} is {}", 
      start, nextPal(start));
}
