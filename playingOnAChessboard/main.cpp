#include <string>
#include <utility>
#include <numeric>
#include <iostream>

#include <vector>

class Suite2
{
public:
  using ull = unsigned long long;

  static std::string game(ull n);

private:
  static ull lcmAllDenom(ull n);
};

std::string Suite2::game(ull n)
{
  ull finalNum = 0;

  auto finalDenom{lcmAllDenom(n)};

  for(ull row=1; row<=n; ++row)
  {
    for(ull col=1; col<=n; ++col)
    {
      finalNum += row * (finalDenom / (row+col));
    }
  }

  int GCD = std::gcd(finalNum,
                  finalDenom);

  finalNum /= GCD;
  finalDenom /= GCD;

  std::string res = "[";
  res.append(std::to_string(finalNum));
  if(finalDenom != 1)
  {
    res.append(", ");
    res.append(std::to_string(finalDenom));
  }
  res.append("]");

  return res;
}

Suite2::ull Suite2::lcmAllDenom(ull n)
{
    ull ans = 2;

    for (ull row = 1; row <= n; ++row)
    {
      for (ull col = 1; col <= n; ++col)
      {
        const auto denom{row + col};
        ans *= denom / std::gcd(denom, ans);
      }
    }

    return ans;
}

Suite2::ull lcmAllDenom(const std::vector<int>& nums)
{
    int ans = nums[0];

    for (const auto num : nums)
    {
      ans *= num / std::gcd(num, ans);
    }

    return ans;
}

int main()
{
  const auto res{Suite2::game(7)};
  //const auto res{Suite2::game(8)};
  std::cout << res << '\n';
}
