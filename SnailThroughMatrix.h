#ifndef SNAILTHROUGHMATRIX_H
#define SNAILTHROUGHMATRIX_H

#include <vector>

std::vector<int> snail(const std::vector<std::vector<int>> &snail_map)
{
  const int size = snail_map.size();
  std::vector<int> result;
  result.reserve(size);

  if (size == 0)
  {
    return result;
  }
  else if(size == 1)
  {
    if(snail_map[0].size() == 1)
    {
      result.push_back(snail_map[0][0]);
    }

    return result;
  }

  // Grab the first row | result.push.apply(result,array[0])
  for(int i=0;i<size;++i)
  {
      result.push_back(snail_map[0][i]);
  }

  // Grab the last column
  for(int i=1;i<size;++i)
  {
      result.push_back(snail_map[i][size-1]);
  }

  // Grab the last row
  for(int i=size-2;i>=0;--i)
  {
      result.push_back(snail_map[size-1][i]);
  }

  // Grab the first column
  for(int i=size-2;i>0;--i)
  {
      result.push_back(snail_map[i][0]);
  }

  std::vector<std::vector<int>> subMatrix(size - 2, std::vector<int>(size - 2));

  // Form the inner matrix
  for (int i=1;i<size-1;++i)
  {
      std::copy(std::begin(snail_map[i]) + 1, std::end(snail_map[i]) - 1,
               std::begin(subMatrix[i-1]));
  }

  //call it recursively
  const std::vector<int> partialRes{snail(subMatrix)};
  result.insert(std::end(result), std::begin(partialRes), std::end(partialRes));

  return result;
}

#endif // SNAILTHROUGHMATRIX_H
