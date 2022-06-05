#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class CountDig
{
public:
    static int nbDig(int n, int d)
    {
      fillSquares(n);

      int cnt = {0};
      for(const auto& num : m_squares)
      {
        cnt += std::count_if(num.begin(), num.end(),
          [d](const char c) -> bool { return d == (c - '0');});
      }

      return cnt;
    }

private:
  static void fillSquares(const int n)
  {
    std::vector<int> intSquares(n);
    std::iota(intSquares.begin(), intSquares.end(), 1);
    std::transform(intSquares.begin(), intSquares.end(), intSquares.begin(), [](const int n) -> int {return n*n;});
    m_squares.reserve(n);
    std::transform(intSquares.begin(), intSquares.end(), std::back_inserter(m_squares),
                   [](const int n) -> std::string {return std::to_string(n);});
  }

  static std::vector<std::string> m_squares;
};

std::vector<std::string> CountDig::m_squares;

int main()
{
  const auto answ = CountDig::nbDig(5750, 0);
  std::cout << answ << '\n';
}
