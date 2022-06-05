#include <iostream>
#include <cctype>
#include <string>

int ChampionRank(int champion, std::string events )
{
  events.append(" "); // for ease of parsing

  auto digit{0};
  auto ret{champion};

  std::size_t pos{0};
  const char delim{' '};
  while((pos = events.find(delim)) != std::string::npos)
  {
    std::string token{events.substr(0, pos)};
    events.erase(0, pos + 1);

    if(!token.empty() && std::isdigit(token[0]))
    {
      digit = std::stoi(token);
    }
    else if(token == "O")
    {
      // 'champion' being overtaken
      if(digit == champion + 1)
      {
        ++ret;
      }
      // 'champion overtakes'
      else if(digit == champion)
        --ret;
    }
    else if(token == "I")
    {
      // someone in front retires
      if(digit < champion)
        --ret;
      // 'champion' retires
      else if(digit == champion)
        return -1;
    }
  }
  return ret;
}

int main()
{
  const auto res = ChampionRank(10, "1 I 10 O 2 I");
  std::cout << res << '\n';
  return 0;
}
