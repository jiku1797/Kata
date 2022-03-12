#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

/* NxN matrix indexed from 1 to N*/
template <typename T>
class DynMatrix
{
public:
  using Row = std::vector<T>;
  using Col = Row;
  using Mat = std::vector<Row>;

  DynMatrix()
  {
  }

  DynMatrix(const std::size_t N) : m_size{N}
  {
    m_matrix.resize(N);
    std::for_each(std::begin(m_matrix), std::end(m_matrix), [N](Row& row)
    {
      row.resize(N);
    });
  }

  DynMatrix(const Mat& arr) : m_matrix{arr}
  {
    if(arr.size() != arr.front().size())
    {
      m_matrix = {{{}}};
      m_size = 0;
    }

    m_size = arr.size();
  }

  Row getRow(const int n) const
  {
    return m_matrix.at(n-1);
  }

  Col getCol(const int n) const
  {
    Col ret{};
    ret.resize(m_size);
    for(std::size_t i=0; i<m_size; ++i)
    {
      ret.at(i) = m_matrix.at(i).at(n-1);
    }

    return ret;
  }

  Mat& getMatrix()
  {
    return m_matrix;
  }

  const Mat& getMatrix() const
  {
    return m_matrix;
  }

  void insert(const std::size_t row, const std::size_t col, const T val)
  {
    m_matrix.at(row-1).at(col-1) = val;
  }

  // replaces row n by row
  void insertRow(const Row& row, const int n)
  {
    for(std::size_t i=0; i<m_size; ++i)
    {
      m_matrix.at(n-1).at(i) = row.at(i);
    }
  }

  T& at(const std::size_t row, const std::size_t col)
  {
    return m_matrix.at(row-1).at(col-1);
  }

  void print() const
  {
    for(const auto& row : m_matrix)
    {
      for(const auto& elem : row)
      {
        std::cout << elem << " ";
      }
      std::cout << '\n';
    }
  }

  void vertMirror()
  {
    for(auto& row : m_matrix)
    {
      std::reverse(row.begin(), row.end());
    }
  }

  void horMirror()
  {
    std::reverse(m_matrix.begin(), m_matrix.end());
  }

private:
  template<typename UnaryFcn>
  void doForEach(UnaryFcn f)
  {
    for(auto& row : m_matrix)
    {
      for(auto& elem : row)
      {
        f(elem);
      }
    }
  }

  Mat m_matrix;
  std::size_t m_size{0};
};

class Opstrings
{
public:
  static std::string vertMirror(const std::string &strng)
  {
    auto matr = strToMatrix(strng);
    matr.vertMirror();
    return matrixToStr(matr);
  }
  static std::string horMirror(const std::string &strng)
  {
    auto matr = strToMatrix(strng);
    matr.horMirror();
    return matrixToStr(matr);
  }

  template<typename StringOp>
  static std::string oper(StringOp sOp, const std::string &s)
  {
    return sOp(s);
  }

private:
  static DynMatrix<char> strToMatrix(std::string str)
  {
    const std::string delimiter = "\n";
    m_size = str.find(delimiter);
    std::vector<std::string> result{};
    result.reserve(m_size);
    std::size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }

    result.push_back(str);

    DynMatrix<char> ret{m_size};

    for(std::size_t i=0; i<result.size(); ++i)
    {
      const auto& current = result.at(i);

      for(std::size_t j=0; j<current.size(); ++j)
      {
        ret.insert(i+1, j+1, current.at(j));
      }
    }

    return ret;
  }
  static std::string matrixToStr(const DynMatrix<char>& mat)
  {
    std::string str;

    for(const auto& row : mat.getMatrix())
    {
      for(const auto& elem : row)
      {
        str.push_back(elem);
      }
      str.append("\n");
    }

    str.erase(str.end()-1, str.end());

    return str;
  }

  static std::size_t m_size;
};

inline std::size_t Opstrings::m_size{0};

int main()
{
  const std::string testStr = "abcd\nefgh\nijkl\nmnop";
  const auto res = Opstrings::vertMirror(testStr);
  std::cout << res << '\n';
  return 0;
}
