#include <vector>
#include <utility>
#include <sstream>
#include <iostream>

class CatRecord
{
public:
  CatRecord(const std::vector<std::string>& categories)
  {
    m_catRecords.reserve(categories.size());
    for(const auto& cat : categories)
    {
      m_catRecords.push_back(std::make_pair(cat, 0));
    }
  }

  auto insert(const std::string& cat, int quant)
  {
    if(auto res = std::find_if(m_catRecords.begin(), m_catRecords.end(),
      [&cat](auto& pair){return pair.first == cat;}); res != m_catRecords.end())
    {
      res->second += quant;
      return true;
    }
    return false;
  }

  auto asString() const
  {
    std::string res{};
    std::stringstream ss;
    for(const auto& rec : m_catRecords)
    {
      ss << "(" << rec.first << " : "
        << rec.second << ") - ";
    }
    auto str{ss.str()};
    str.erase(str.end()-3, str.end());
    return str;
  }

private:
  std::vector<std::pair<std::string, int>> m_catRecords;
};

class StockList
{
public:
  static std::string stockSummary(std::vector<std::string>& lstOfArt, std::vector<std::string>& categories);

private:
  static int getQuantity(const std::string& str);
};

std::string StockList::stockSummary(std::vector<std::string>& lstOfArt, std::vector<std::string>& categories)
{
  if(lstOfArt.empty() || categories.empty())
      return "";

  CatRecord catRecords{categories};

  for(const auto& item : lstOfArt)
  {
    const std::string cat{item.front()};
    auto quant{getQuantity(item)};
    catRecords.insert(cat, quant);
  }

  return catRecords.asString();
}

int StockList::getQuantity(const std::string& str)
{
  const auto res{str.find(' ')};
  if(res != std::string::npos)
    return std::stoi(str.substr(res + 1));

  return -1;
}

int main(int argc, const char* argv[])
{
  std::vector<std::string> art = {"ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"};
  std::vector<std::string> cd = {"A", "B"};

  std::cout << StockList::stockSummary(art, cd) << '\n';
}
