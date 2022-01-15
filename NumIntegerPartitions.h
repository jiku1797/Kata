#ifndef NUMINTEGERPARTITIONS_H
#define NUMINTEGERPARTITIONS_H

#include <vector>
#include <algorithm>

using ull = unsigned long long;
using Matrix = std::vector<std::vector<ull>>;

ull numPartitions(const int n, const int m, Matrix& memo)
{
  if (n == 0) return 1ull;
  if (m == 0 ) return 0ull;
  if (n < 0) return 0ull;

  if (memo.at(n-1).size() == 0)
  {
    std::for_each(std::begin(memo), std::end(memo), [m](std::vector<ull>& mem)
      {
        mem.resize(m, 0ull);
      });
  }

  ull result = memo.at(n-1).at(m-1);

  if (result == 0ull)
  {
    result = numPartitions(n-m, m, memo) + numPartitions(n, m-1, memo);

    memo.at(n-1).at(m-1) = result;
  };

  return result;
}

ull exp_sum(unsigned int n)
{
  Matrix memo;

  memo.resize(n);

  return numPartitions(n, n, memo);
}

#endif // NUMINTEGERPARTITIONS_H
