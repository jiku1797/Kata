#ifndef MOVES_IN_SQUARED_STRINGS_H
#define MOVES_IN_SQUARED_STRINGS_H

#include <string>
#include <array>

/* Matrix indexed from 1 to N*/
template <typename T, int N>
class Matrix
{
  using Mat = std::array<std::array<T, N>, N>;

public:
  Matrix()
  {
    doForEach([](T& elem){elem = T();});
  }

  Matrix(const std::array<std::array<T, N>, N>& arr) : m_matrix{arr}
  {
  }

  void insert(const std::size_t row, const std::size_t col, const T val)
  {
    m_matrix.at(row-1).at(col-1) = val;
  }

  T at(const std::size_t row, const std::size_t col)
  {
    return m_matrix.at(row-1).at(col-1);
  }

  void diagSym()
  {

  }

  void rotCounter();

  void print()
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

private:
    static Matrix<char, 4> strToMatrix(const std::string& str);
};

std::string Opstrings4::diag2Sym(const std::string& strng)
{

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

}

#endif // MOVES_IN_SQUARED_STRINGS_H
