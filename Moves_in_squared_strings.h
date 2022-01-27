#ifndef MOVES_IN_SQUARED_STRINGS_H
#define MOVES_IN_SQUARED_STRINGS_H

#include <string>
#include <array>
#include <sstream>

/* NxN matrix indexed from 1 to N*/
template <typename T, int N>
class Matrix
{
  using Mat = std::array<std::array<T, N>, N>;

public:
  Matrix()
  {
    doForEach([](T& elem){elem = T();});
  }

  Matrix(const Mat& arr) : m_matrix{arr}
  {
  }

  void insert(const std::size_t row, const std::size_t col, const T val)
  {
    m_matrix.at(row-1).at(col-1) = val;
  }

  T& at(const std::size_t row, const std::size_t col)
  {
    return m_matrix.at(row-1).at(col-1);
  }

  // Mirroring through non-main diagonal
  void diagSym()
  {
    for(std::size_t i=0; i<N; ++i)
    {
      for(std::size_t j=0; i+j<N; ++j)
      {
        std::swap(at(i+1, j+1), at(4-j, 4-i));
      }
    }
  }

  void rotCounter();

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
};

class Opstrings4
{
public:
    static std::string diag2Sym(const std::string& strng);
    static std::string rot90Counter(const std::string& strng);
    static std::string selfieDiag2Counterclock(const std::string& strng);
    static std::string oper(std::string (*fcnPtr)(const std::string&), const std::string& s);

public:
    static Matrix<char, 4> strToMatrix(const std::string& str);
    static std::string matrixToStr(const Matrix<char, 4>& str);
};

std::string Opstrings4::diag2Sym(const std::string& strng)
{
  Matrix<char, 4> mat = strToMatrix(strng);
  mat.diagSym();
  return matrixToStr(mat);
}

std::string Opstrings4::rot90Counter(const std::string& strng)
{

}

std::string Opstrings4::selfieDiag2Counterclock(const std::string& strng)
{

}

std::string Opstrings4::oper(std::string (*fcnPtr)(const std::string&), const std::string& s)
{

}

Matrix<char, 4> Opstrings4::strToMatrix(const std::string& str)
{
  auto result = std::array<std::string, 4>{};
  auto ss = std::stringstream{str};
  auto idx{0};

  for (std::string line; std::getline(ss, line, '\n');)
  {
    result.at(idx) = line;
    ++idx;
  }

  Matrix<char, 4> ret{};

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

std::string Opstrings4::matrixToStr(const Matrix<char, 4>& mat)
{
  std::string str;
  return str;
}

#endif // MOVES_IN_SQUARED_STRINGS_H
