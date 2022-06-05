#include <iostream>
#include<cstdint>
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>

std::vector<int> primeExponents(int64_t n)
{
  std::vector<int> exponents;
  auto cnt{0};
  while (n % 2 == 0)
  {
      ++cnt;
      n /= 2;
  }
  exponents.push_back(cnt);

  for (int i = 3; i <= sqrt(n); i += 2)
  {
    cnt = 0;
    while (n % i == 0)
    {
        ++cnt;
        std::cout << "Adding exponent for prime " << i << '\n';
        n /= i;
    }
    exponents.push_back(cnt);
  }

  if (n > 2)
    exponents.push_back(1);

  return exponents;
}

template <typename T>
void print(const T& coll)
{
  for(const auto& elem : coll)
  {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int64_t lcmCardinality(int64_t n)
{
  const auto exponents{primeExponents(n)};
  print(exponents);
  const auto comb = std::accumulate(exponents.begin(), exponents.end(), 1, [](int a, int b)
                    {
                      return a * (2*b+1);
                    });
  return (comb + 1) / 2;
}

int main()
{
  std::cout << lcmCardinality(24) << '\n';
}
