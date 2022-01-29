#ifndef MOVES_IN_SQUARED_STRINGS_H
#define MOVES_IN_SQUARED_STRINGS_H

#include <string>
#include <vector>
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

  // Mirroring through non-main diagonal
  void diagSym()
  {
    for(std::size_t i=0; i<m_size; ++i)
    {
      for(std::size_t j=0; i+j<m_size; ++j)
      {
        std::swap(at(i+1, j+1), at(m_size-j, m_size-i));
      }
    }
  }

  void rotCounter()
  {
    DynMatrix rotMat{m_size};
    for(std::size_t i=m_size; i>=1; --i)
    {
      const auto col = getCol(i);
      rotMat.insertRow(col, m_size-i+1);
    }

    m_matrix = rotMat.getMatrix();
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

class Opstrings4
{
public:
    static std::string diag2Sym(const std::string& strng);
    static std::string rot90Counter(const std::string& strng);
    static std::string selfieDiag2Counterclock(const std::string& strng);
    static std::string oper(std::string (*fcnPtr)(const std::string&), const std::string& s);

private:
    static DynMatrix<char> strToMatrix(const std::string& str);
    static std::string matrixToStr(const DynMatrix<char>& mat);

    static std::size_t m_size;
};

inline std::size_t Opstrings4::m_size{0};

std::string Opstrings4::diag2Sym(const std::string& strng)
{
  DynMatrix<char> mat = strToMatrix(strng);
  mat.diagSym();
  return matrixToStr(mat);
}

std::string Opstrings4::rot90Counter(const std::string& strng)
{
  DynMatrix<char> mat = strToMatrix(strng);
  mat.rotCounter();
  return matrixToStr(mat);
}

std::string Opstrings4::selfieDiag2Counterclock(const std::string& strng)
{
  const auto orig = strToMatrix(strng);
  auto symMatr = strToMatrix(strng);
  symMatr.diagSym();
  auto rotMatr = strToMatrix(strng);
  rotMatr.rotCounter();

  std::string ret;

  for(std::size_t i=1; i<=m_size; ++i)
  {
    const auto row2Str = [&ret](const std::vector<char>& row) -> std::string
    {
      std::string rowStr{};

      for(const auto ch : row)
      {
        ret.push_back(ch);
      }
      ret.push_back('|');

      return rowStr;
    };

    ret.append(row2Str(orig.getRow(i)));
    ret.append(row2Str(symMatr.getRow(i)));
    ret.append(row2Str(rotMatr.getRow(i)));
    ret.erase(ret.end()-1, ret.end());
    ret.append("\n");
  }

  ret.erase(ret.end()-1,ret.end());

  return ret;
}

std::string Opstrings4::oper(std::string (*fcnPtr)(const std::string&), const std::string& s)
{
  return fcnPtr(s);
}

DynMatrix<char> Opstrings4::strToMatrix(const std::string& str)
{
  std::string strCpy = str;
  const std::string delimiter = "\n";
  m_size = str.find(delimiter);
  std::vector<std::string> result{};
  result.reserve(m_size);
  std::size_t pos = 0;
  while ((pos = strCpy.find(delimiter)) != std::string::npos)
  {
      result.push_back(strCpy.substr(0, pos));
      strCpy.erase(0, pos + delimiter.length());
  }

  result.push_back(strCpy);

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

std::string Opstrings4::matrixToStr(const DynMatrix<char>& mat)
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

#endif // MOVES_IN_SQUARED_STRINGS_H
