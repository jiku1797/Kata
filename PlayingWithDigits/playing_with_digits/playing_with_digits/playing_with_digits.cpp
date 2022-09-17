/*
   Some numbers have funny properties. For example:

   89 --> 8¹ + 9² = 89 * 1

   695 --> 6² + 9³ + 5⁴= 1390 = 695 * 2

   46288 --> 4³ + 6⁴+ 2⁵ + 8⁶ + 8⁷ = 2360688 = 46288 * 51

   Given a positive integer n written as abcd... (a, b, c, d... being digits) and a positive integer p

   we want to find a positive integer k, if it exists, such that the sum of the digits of n taken to the successive powers of p is equal to k * n.
   In other words:

   Is there an integer k such as : (a ^ p + b ^ (p+1) + c ^(p+2) + d ^ (p+3) + ...) = n * k

   If it is the case we will return k, if not return -1.

   Note: n and p will always be given as strictly positive integers.
*/
#include <iostream>
#include <array>
#include <cmath>

static constexpr auto maxDigits{ 16 };

class DigPow
{
public:
   static int digPow(int n, int p)
   {
      computeDigits(n);
      auto powSum{ 0 };
      for (const auto d : m_digits)
      {
         if (d == -1)
            break;

         powSum += std::pow(d, p++);
      }

      if (powSum % n == 0)
         return powSum / n;

      return -1;
   }

private:
   static void computeDigits(int n)
   {
      const auto numDigits{ static_cast<int>(std::floor(std::log10(n))) + 1 };
      m_digits[numDigits] = -1; // sentinel
      auto idx{ numDigits - 1 };

      while (n != 0)
      {
         m_digits[idx--] = n % 10;
         n /= 10;
      }

   }
   static std::array<int, maxDigits + 1> m_digits;
};

std::array<int, maxDigits + 1> DigPow::m_digits;

int main()
{
   std::cout << DigPow::digPow(695, 2) << '\n';
}
