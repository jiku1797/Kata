#include <vector>
#include <algorithm>
#include <iostream>

long queueTime(std::vector<int> customers, int n)
{
  if(customers.size() <= static_cast<std::size_t>(n))
  {
    const auto itMax = std::max_element(customers.begin(), customers.end());
    if(itMax != customers.end())
      return *itMax;
    else
      return 0l;
  }

  auto totTime{0l};
  std::size_t next{static_cast<std::size_t>(n)};

  while(next <= customers.size())
  {
    const auto deltaT{*std::min_element(customers.begin(), customers.begin()+next)};
    totTime += deltaT;
    auto numFreeTills{0};
    std::for_each(customers.begin(), customers.begin()+next, [deltaT, &numFreeTills](int& time) mutable
      {
        if(time > 0)
        {
          time -= deltaT;
          if(time == 0)
          {
            ++numFreeTills;
            time = 1000000;
          }
        }
      });

    next += numFreeTills;
  }

  return totTime;
}

int main(int argc, const char* argv[])
{
  std::cout << queueTime(std::vector<int>{2,2,3,3,4,4}, 2) << '\n';
}

