#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/*
 * You have a positive number n consisting of digits. You can do at most one operation:
 * Choosing the index of a digit in the number, remove this digit at that index and insert
 * it back to another or at the same place in the number in order to find the smallest
 * number you can get.
 *
 * Task:
 * Return an array or a tuple or a string depending on the language (see "Sample Tests") with

 * the smallest number you got
 * the index i of the digit d you took, i as small as possible
 * the index j (as small as possible) where you insert this digit d to have the smallest number.
 * Examples:
 * smallest(261235) --> [126235, 2, 0] or (126235, 2, 0) or "126235, 2, 0"
*/

class ToSmallest
{
  using ll = long long;
public:
    static std::vector<long long> smallest(long long n)
    {
      auto digits = intToArray(n);
      const auto lRes{traverseFromLeft(digits)};
      auto digits2 = intToArray(n);
      const auto rRes{traverseFromRight(digits2)};

      return (lRes.at(0) < rRes.at(0)) ? lRes : rRes;
    }

private:
    static std::vector<ll> traverseFromLeft(std::vector<ll>& digits)
    {
      auto curIt{std::begin(digits)};
      auto minIt{std::begin(digits)};
      while(curIt != std::end(digits))
      {
        minIt = std::min_element(std::next(curIt), std::end(digits));
        if(*curIt > *minIt)
        {
          std::rotate(curIt, minIt, minIt+1);
          break;
        }
        ++curIt;
      }
      auto fromIdx{std::distance(std::begin(digits), minIt)};
      auto toIdx{std::distance(std::begin(digits), curIt)};
      if(fromIdx == toIdx + 1)
        std::swap(fromIdx, toIdx);

      return {arrayToInt(digits), fromIdx, toIdx};
    }

    static std::vector<ll> traverseFromRight(std::vector<ll>& digits)
    {
      auto curIt{std::prev(std::end(digits))};
      auto maxIt{std::prev(std::end(digits))};
      //auto fromIdx{0};

      while(curIt != std::begin(digits))
      {
        maxIt = std::max_element(std::begin(digits), curIt);
        if(*curIt < *maxIt)
        {
          //fromIdx = std::distance(std::begin(digits), maxIt);
          std::rotate(maxIt, maxIt+1, std::end(digits));
          break;
        }
        --curIt;
      }

      auto fromIdx{std::distance(std::begin(digits), maxIt)};
      auto toIdx{std::distance(std::begin(digits), curIt)};

      return {arrayToInt(digits), fromIdx, toIdx};
    }

    static std::vector<ll> intToArray(ll n)
    {
      std::vector<ll> digits;
      while(n)
      {
        const auto rem{n % 10};
        n /= 10;
        digits.push_back(rem);
      }
      std::reverse(std::begin(digits), std::end(digits));
      return digits;
    }

    static ll arrayToInt(const std::vector<ll>& digits)
    {
      ll res{0};
      int pow{1};
      for(auto it{digits.crbegin()}; it!=digits.crend(); ++it)
      {
        res += *it * pow;
        pow *= 10;
      }

      return res;
    }
};

int main()
{
  const auto res = ToSmallest::smallest(209917);
  std::cout << "[" << res.at(0) << ", "
            << res.at(1) << ", "
            << res.at(2) << "]\n";

  return 0;
}
