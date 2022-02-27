#include <numeric>
#include <string>
#include <vector>
#include <iostream>

template<class T>
inline T gcd(T a, T b)
{
  while(b)
  {
    auto t = a % b;
    a = b;
    b = t;
  }

  return a;
}

class ModSystem
{
public:
    static std::string fromNb2Str(int n, std::vector<int>& sys)
    {
      std::string ret{"Not applicable"};
      const auto prod = std::accumulate(std::begin(sys), std::end(sys),
                                       1, [](auto f, auto s){return f * s;});

      if(n>prod) return ret;
      if(!areCoPrime(sys)) return ret;

      ret.clear();
      ret.push_back('-');
      for(auto num : sys)
      {
        const auto rem{n % num};
        ret.append(std::to_string(rem));
        ret.append("--");
      }
      ret.pop_back();
      return ret;
    }

private:
  static bool areCoPrime(std::vector<int>& nums)
  {
    for(auto it=nums.begin(); it!=nums.end()-1; ++it)
    {
      for(auto itt=it+1; itt!=nums.end();++itt)
      {
        if(gcd(*it, *itt) > 1) return false;
      }
    }

    return true;
  }
};

int main()
{
  constexpr auto testNum{11};
  std::vector<int> testSys{2,3,5};
  const auto res{ModSystem::fromNb2Str(testNum, testSys)};
  std::cout << res << '\n';
  return 0;
}
