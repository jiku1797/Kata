#include <array>
#include <iostream>

struct Node
{
  char m_id{'A'};
  bool m_visited{false};
};

template <typename T>
class Matrix3_3
{
public:
  using Vec = std::array<T, 3>;

  template <typename UnaryOp>
  void doForEach(UnaryOp uop)
  {
    for(auto& row : m_data)
    {
      for(auto& elem : row)
      {
        uop(elem);
      }
    }
  }
private:
  std::array<Vec, 3> m_data;
};

class NumPad
{
public:
  NumPad()
  {
    char currentLetter{'A'};
    auto initNums = [&currentLetter](Node& node) mutable
    {
      node.m_id = currentLetter++;
    };
    m_numbers.doForEach(initNums);
  }

  void print()
  {
    auto printNode = [](const Node& node)
    {
      std::cout << node.m_id << " ";
    };

    m_numbers.doForEach(printNode);
  }

private:
  Matrix3_3<Node> m_numbers;
};

unsigned int countPatternsFrom(char firstDot, unsigned short length)
{
}

int main()
{
  NumPad np{};
  np.print();
  return 0;
}
