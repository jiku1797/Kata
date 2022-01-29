#ifndef FMATRIX_H
#define FMATRIX_H

/* NxN matrix indexed from 1 to N*/
template <typename T, int N>
class Matrix
{
  using Row = std::array<T, N>;
  using Mat = std::array<Row, N>;
  using Col = Row;

public:
  Matrix()
  {
    doForEach([](T& elem){elem = T();});
  }

  Matrix(const Mat& arr) : m_matrix{arr}
  {
  }

  Row getRow(const int n)
  {
    return m_matrix.at(n-1);
  }

  Row getRow(const int n) const
  {
    return m_matrix.at(n-1);
  }

  Col getCol(const int n)
  {
    Col ret{};
    for(std::size_t i=0; i<N; ++i)
    {
      ret.at(i) = m_matrix.at(i).at(n-1);
    }

    return ret;
  }

  Col getCol(const int n) const
  {
    Col ret{};
    for(std::size_t i=0; i<N; ++i)
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
    for(std::size_t i=0; i<N; ++i)
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
    for(std::size_t i=0; i<N; ++i)
    {
      for(std::size_t j=0; i+j<N; ++j)
      {
        std::swap(at(i+1, j+1), at(4-j, 4-i));
      }
    }
  }

  void rotCounter()
  {
    Matrix rotMat;
    for(std::size_t i=N; i>=1; --i)
    {
      const auto col = getCol(i);
      rotMat.insertRow(col, N-i+1);
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
};

#endif // FMATRIX_H
