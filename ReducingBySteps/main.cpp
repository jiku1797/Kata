#include <iostream>
#include <vector>

class Operarray
{
public:
    static long long gcdi(long long x, long long y)
    {
      if(x < 0)
        x *= (-1);
      if(y < 0)
        y *= (-1);

      if (y == 0)
        return x;
      return gcdi(y, x % y);
    }

    static long long lcmu(long long a, long long b)
    {
      if((a == 0) && (b == 0))
        return 0;

      auto ans = (a / gcdi(a, b)) * b;
      if(ans < 0)
        ans *= (-1);
      return ans;
    }

    static long long som(long long a, long long b) {return a + b;}
    static long long maxi(long long a, long long b) {return std::max(a,b);}
    static long long mini(long long a, long long b) {return std::min(a,b);}

    template <typename Oper>
    static long long oper(Oper op, long long a, long long b);

    template <typename Oper>
    static std::vector<long long> operArray(Oper op, std::vector<long long> &arr, long long init);
};

template <typename Oper>
long long Operarray::oper(Oper, long long a, long long b)
{
  return 0;
}

template <typename Oper>
std::vector<long long> Operarray::operArray(Oper op, std::vector<long long>& arr, long long init)
{
  // r = [r[0] = f(init, a[0]), r[1] = f(r[0], a[1]), r[2] = f(r[1], a[2]), ...]
  std::vector<long long> ret;
  ret.reserve(arr.size());

  auto first = op(init, arr.at(0));
  ret.push_back(first);

  for(auto i = 1; i < arr.size(); ++i)
  {
    ret.push_back(op(ret.at(i-1), arr.at(i)));
  }

  return ret;
}

/*
a = [18, 69, -90, -78, 65, 40]
oper_array(gcd, a, a[0]) => [18, 3, 3, 3, 1, 1]
oper_array(lcm, a, a[0]) => [18, 414, 2070, 26910, 26910, 107640]
oper_array(sum, a, 0) => [18, 87, -3, -81, -16, 24]
oper_array(min, a, a[0]) => [18, 18, -90, -90, -90, -90]
oper_array(max, a, a[0]) => [18, 69, 69, 69, 69, 69]
*/

int main()
{
  std::vector testVec{18ll, 69ll, -90ll, -78ll, 65ll, 40ll};
  const auto result = Operarray::operArray(Operarray::lcmu, testVec, testVec.at(0));
  for(auto elem : result)
  {
    std::cout << elem << '\n';
  }
}
