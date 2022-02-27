#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cctype>
/*
 * The goal of this exercise is to convert a string to a new string where each
 * character in the new string is "(" if that character appears only once in the
 * original string, or ")" if that character appears more than once in the original
 * string. Ignore capitalization when determining if a character is a duplicate.

 * Examples
 * "din"      =>  "((("
 * "recede"   =>  "()()()"
 * "Success"  =>  ")())())"
 * "(( @"     =>  "))(("
*/

std::string duplicate_encoder(const std::string& word)
{
  auto sortedStr{word};
  std::for_each(sortedStr.begin(), sortedStr.end(), [](char& c){c = std::tolower(c);});
  std::sort(sortedStr.begin(), sortedStr.end());
  std::unordered_map<char, bool> charMult; // true if > 1 occurrence

  for(auto it=sortedStr.begin(); it!=sortedStr.end();)
  {
    const auto currVal{*it};
    if((it != sortedStr.end() - 1) && (currVal == *(it+1)))
    {
      charMult.insert({currVal, true});
      while((it != sortedStr.end()) && (*it) == currVal){++it;}
    }
    else
    {
      charMult.insert({currVal, false});
      ++it;
    }
  }

  std::string ret{};
  ret.reserve(word.size());

  for(auto c : word)
  {
    c = std::tolower(c);
    if(charMult.at(c))
    {
      ret.push_back(')');
    }
    else
    {
      ret.push_back('(');
    }
  }

  return ret;
}


int main()
{
  const std::string testStr{"Success"};
  const auto res{duplicate_encoder(testStr)};
  std::cout << res << '\n';
  return 0;
}
