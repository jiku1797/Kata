#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

std::vector<std::pair<long long, int>> primeFactors(long long n)
{
   std::vector<std::pair<long long, int>> fact{};
   auto exp{ 0 };
   while (n % 2 == 0)
   {
      ++exp;
      n = n / 2;
   }
   if (exp > 0)
   {
      fact.emplace_back(2ll, exp);
   }

   for (long long i = 3; i <= sqrt(n); i += 2)
   {
      exp = 0;
      while (n % i == 0)
      {
         ++exp;
         n /= i;
      }
      if (exp > 0)
      {
         fact.emplace_back(i, exp);
      }
   }

   if (n > 2)
   {
      fact.emplace_back(n, 1);
   }
   return fact;
}

long long gcd(long long a, long long b)
{
   if (b == 0)
      return a;
   return gcd(b, a % b);
}

long long findLcm(const std::vector<long long>& arr)
{
   auto ans = arr[0];

   for (const auto i : arr)
      ans = (i * ans) / gcd(i, ans);

   return ans;
}

long long Carmichael_pe(const std::pair<long long, int>& pe)
{
   const auto [p, e] = pe;
   if (p > 2)
   {
      return std::pow(p, e - 1) * (p - 1);
   }
   else
   {
      if (e < 3)
      {
         return std::pow(2, e - 1);
      }
      else
      {
         return std::pow(2, e - 2);
      }
   }
}

std::vector<long long> getLambdaVec(const std::vector<std::pair<long long, int>>& pe)
{
   std::vector<long long> ret{};
   ret.reserve(pe.size());
   for (const auto& p : pe)
   {
      ret.push_back(Carmichael_pe(p));
   }
   return ret;
}

long long Carmichael(long long n)
{
   if (n <= 0)
      return 0;
   else if (n == 1)
      return 1;

   const auto pf{ primeFactors(n) };
   if(pf.size() == 1)
   {
      if(pf[0].second == 1)
      {
         return n-1;
      }
   }
   const auto lambdaVec{ getLambdaVec(pf) };
   return findLcm(lambdaVec);
}

int main(int argc, char* argv[])
{
   const auto res{Carmichael(3181169083)};
   std::cout << res << '\n';
   return 0;
}