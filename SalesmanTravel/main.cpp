#include <iostream>
#include <string>
#include <vector>
#include <utility>

class SalesmanTravel
{
  using Address = std::pair<std::string, int>;

public:
  static std::string travel(const std::string& orgr, std::string zipcode)
  {
    m_addr.clear();
    parseToMap(orgr);
    std::string streetNoTail{};
    std::string ret{zipcode};
    ret.push_back(':');

    for(const auto& [zip, addr] : m_addr)
    {
      if(zip.compare(zipcode) == 0)
      {
        ret.append(addr.first);
        ret.push_back(',');

        streetNoTail.append(std::to_string(addr.second));
        streetNoTail.push_back(',');
      }
    }

    if(ret.back() != ':')
    {
      ret.back() = '/';
    }
    else
    {
      ret.push_back('/');
    }

    if(streetNoTail.size() > 0)
    {
      streetNoTail.erase(streetNoTail.size()-1);
    }

    ret.append(streetNoTail);

    return ret;
  }

private:
  static void parseToMap(std::string ad)
  {
    std::size_t pos{0};
    const std::string delim{","};
    std::string current{};

    while((pos = ad.find(delim)) != std::string::npos)
    {
      current = ad.substr(0, pos);
      ad.erase(0, pos + delim.length());
      parseSingleAddress(current);
    }
  }

  static void parseSingleAddress(const std::string& singleAddress)
  {
    const auto pos{singleAddress.find(" ")};
    const auto pos2{singleAddress.size() - 9};

    const auto streetNo{std::stoi(singleAddress.substr(0, pos))};
    const auto addr{singleAddress.substr(pos+1, pos2-pos-1)};
    const auto zipCode{singleAddress.substr(pos2+1)};

    const Address ad = std::make_pair(addr, streetNo);
    m_addr.push_back({zipCode, ad});
  }

  static void printMap()
  {
    for(const auto& [zip, addr] : m_addr)
    {
      std::cout << "Zip Code = "
                << zip << "\t==>\t"
                << "Address = " << addr.first
                << "\tStreet = " << addr.second
                << '\n';
    }
  }
  static std::vector<std::pair<std::string, Address>> m_addr;
};

std::vector<std::pair<std::string, SalesmanTravel::Address>> SalesmanTravel::m_addr{};

int main()
{
  const std::string ad = "123 Main Street St. Louisville OH 43071,432 Main Long Road St. Louisville OH 43071,786 High Street Pollocksville NY 56432,"
      "54 Holy Grail Street Niagara Town ZP 32908,3200 Main Rd. Bern AE 56210,1 Gordon St. Atlanta RE 13000,"
      "10 Pussy Cat Rd. Chicago EX 34342,10 Gordon St. Atlanta RE 13000,58 Gordon Road Atlanta RE 13000,"
      "22 Tokyo Av. Tedmondville SW 43098,674 Paris bd. Abbeville AA 45521,10 Surta Alley Goodtown GG 30654,"
      "45 Holy Grail Al. Niagara Town ZP 32908,320 Main Al. Bern AE 56210,14 Gordon Park Atlanta RE 13000,"
      "100 Pussy Cat Rd. Chicago EX 34342,2 Gordon St. Atlanta RE 13000,5 Gordon Road Atlanta RE 13000,"
      "2200 Tokyo Av. Tedmondville SW 43098,67 Paris St. Abbeville AA 45521,11 Surta Avenue Goodtown GG 30654,"
      "45 Holy Grail Al. Niagara Town ZP 32918,320 Main Al. Bern AE 56215,14 Gordon Park Atlanta RE 13200,"
      "100 Pussy Cat Rd. Chicago EX 34345,2 Gordon St. Atlanta RE 13222,5 Gordon Road Atlanta RE 13001,"
      "2200 Tokyo Av. Tedmondville SW 43198,67 Paris St. Abbeville AA 45522,11 Surta Avenue Goodville GG 30655,"
      "2222 Tokyo Av. Tedmondville SW 43198,670 Paris St. Abbeville AA 45522,114 Surta Avenue Goodville GG 30655,"
      "2 Holy Grail Street Niagara Town ZP 32908,3 Main Rd. Bern AE 56210,77 Gordon St. Atlanta RE 13000";
  SalesmanTravel::travel(ad, "AA 45522");
  const auto ret = SalesmanTravel::travel(ad, "YY 45098"); // "AA 45522:Paris St. Abbeville,Paris St. Abbeville/67,670")

  std::cout << ret << '\n';

  return 0;
}
