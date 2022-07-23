#include <bitset>
#include <string>
#include <iostream>
#include <limits.h>
#include <algorithm>

namespace coding
{
   std::string encodeDigit(const unsigned char c)
   {
      std::bitset<sizeof(char)* CHAR_BIT> bs{ c - static_cast<unsigned long long>('0') };
      auto bsStr{ bs.to_string() };
      auto firstOne = std::find(bsStr.begin(), bsStr.end(), '1');
      if (firstOne != bsStr.end())
         bsStr = bsStr.substr(std::distance(bsStr.begin(), firstOne));
      else
         bsStr = "0";
      const auto length{ bsStr.size() - 1 };
      std::string zeros(length, '0');
      zeros.push_back('1');
      return zeros.append(bsStr);
   }

   std::string code(const std::string& strng)
   {
      std::string encoding{};
      for (const auto c : strng)
      {
         encoding += encodeDigit(c);
      }
      return encoding;
   }

   char decodeDigit(const std::string& digit, int numZeros)
   {
      std::bitset<sizeof(char)* CHAR_BIT> bs{ digit.substr(numZeros + 1) };
      return bs.to_ulong() + '0';
   }

   std::string decode(const std::string& str)
   {
      std::string decoding{};
      std::size_t idx{ 0 };
      auto numZeros{ 0 };
      auto prev{ str.begin() };
      while (idx < str.size())
      {
         const auto firstOne{ std::find(prev, str.end(), '1') };
         numZeros = std::distance(prev, firstOne);
         decoding.push_back(decodeDigit(str.substr(idx, 2 * numZeros + 2), numZeros));
         idx += 2 * numZeros + 2;
         prev += 2 * numZeros + 2;
      }
      return decoding;
   }
}

int main(int argc, char* argv[])
{
   //std::cout << coding::encodeDigit('3') << '\n';
   //std::cout << coding::decode("11121314"); //"0011121314") --> "1010111111011011011111001100"
   std::cout << coding::decode("1010111111011011011111001100"); //"1010111111011011011111001100") -> "0011121314"
   return 0;
}
