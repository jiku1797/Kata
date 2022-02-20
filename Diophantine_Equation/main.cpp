#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/*
* In mathematics, a Diophantine equation is a polynomial equation, usually with two or more unknowns, such that only the integer solutions are sought or studied.
* In this kata we want to find all integers x, y (x >= 0, y >= 0) solutions of a diophantine equation of the form:
* x2 - 4 * y2 = n
* (where the unknowns are x and y, and n is a given positive number) in decreasing order of the positive xi.
* If there is no solution return [] or "[]" or "". (See "RUN SAMPLE TESTS" for examples of returns).
*/

static constexpr bool isInt(const double fValue)
{
  int tmp = static_cast<int>(fValue);

  if(fValue - tmp > 0)
    return false;
  else
    return true;
}

class FactorFinder
{
public:
  explicit FactorFinder(const long long n) : m_num{n}
  {
    m_isSquare = isInt(sqrt(m_num));
  }

  std::vector<long long> factors() const
  {
    std::vector<long long> factors = {1, m_num};
    const auto sqroot{static_cast<long long>(sqrt(m_num))};

    for(long long i=2; i<=sqroot; ++i)
    {
      if(m_num % i == 0)
      {
        factors.push_back(i);
        factors.push_back(m_num/i); // also complementary factor
      }
    }

    // for perfect squares
    if(m_isSquare)
    {
      factors.pop_back();
    }

    return factors;
  }

  private:
  long long m_num;
  bool m_isSquare{false};
};

class Dioph
{
  public:
  static std::vector<std::pair <long, long>> solEquaStr(long long n)
  {
    std::vector<std::pair <long, long>> solutions{};
    FactorFinder ff{n};
    const auto factors{ff.factors()};
    std::for_each(factors.begin(), factors.end(), [&solutions, n](const long long f)
    {
      const auto possX = (f + n/f) / 2.0;
      const auto possY = (f - n/f) / 4.0;

      if(isValid(possX) && isValid(possY))
      {
        solutions.emplace_back(std::make_pair(static_cast<long long>(possX),
                                              static_cast<long long>(possY)));
      }
    });

    return solutions;
  }

private:
  static bool isValid(const double num)
  {
    bool valid{isInt(num)};

    if(valid)
      valid = valid && (num >= 0);

    return valid;
  }

};

int main()
{
  const auto solutions = Dioph::solEquaStr(90005);
  for(const auto& [x, y] : solutions)
  {
    std::cout << x << ", " << y << '\n';
  }
  return 0;
}
