#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <exception>

enum class Sign{plus = 0, minus, none};

class TokenHandler
{
public:
  void handleToken(const std::string& token);
  std::vector<int> lhs;
  std::vector<int> rhs;
  bool xOnLhs = true;
private:
  bool beforeEquals = true;
  Sign sign = Sign::none;
};

void TokenHandler::handleToken(const std::string& token)
{
  if(token == "+")
  {
    sign = Sign::plus;
  }
  else if(token == "-")
  {
    sign = Sign::minus;
  }
  else if(token == "=")
  {
      sign = Sign::none;
      beforeEquals = false;
  }
  else if(token == "x")
  {
    if((!beforeEquals && (sign != Sign::minus))|| (beforeEquals && (sign == Sign::minus)))
      xOnLhs = false;
    sign = Sign::none;
  }
  else if(token.empty())
  {
    sign = Sign::none;
  }
  else
  {
    int num;
    try
    {
      num = stoi(token);
    }
    catch(const std::exception& e)
    {
      std::cout << "An exception occured: "
                << e.what() << '\n';
    }
    if(sign == Sign::plus || sign == Sign::none)
    {
      if(beforeEquals)
      {
        lhs.push_back(num);
      }
      else
      {
        rhs.push_back(num);
      }
    }
    else if (sign == Sign::minus)
    {
      if(beforeEquals)
      {
        lhs.push_back(-num);
      }
      else
      {
        rhs.push_back(-num);
      }
    }

    sign = Sign::none;
  }
}

int solve(const std::string& eqn)
{
  TokenHandler th;
  std::string eq = eqn;
  std::string delim{" "};
  std::string token;
  std::size_t pos{0};
  while((pos = eq.find(delim)) != std::string::npos)
  {
    token = eq.substr(0, pos);
    th.handleToken(token);
    eq.erase(0, pos + delim.length());
  }
  th.handleToken(eq);

  const auto sumLeft{std::accumulate(th.lhs.begin(), th.lhs.end(), 0)};
  const auto sumRight{std::accumulate(th.rhs.begin(), th.rhs.end(), 0)};

  const auto answ = th.xOnLhs ? sumRight - sumLeft : sumLeft - sumRight;
  return answ;
}

int main()
{
  const std::string eq{"x + 1 = 9 - 2"};
  const auto answ = solve(eq);
  std::cout << answ << '\n';
}
