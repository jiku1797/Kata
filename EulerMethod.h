#ifndef EULERMETHOD_H
#define EULERMETHOD_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

class EulerOde
{
public:
  static double exEuler(int nb);
};

namespace eulerOdeHelpers
{
  double trueVal(const double xVal)
  {
    double val{1};
    val += 0.5 * std::exp((-4) * xVal);
    val -= 0.5 * std::exp((-2) * xVal);

    return val;
  }

  double derivative(const double xVal, const double yVal)
  {
    double dVal{2};
    dVal -= std::exp((-4) * xVal);
    dVal -= 2 * yVal;

    return dVal;
  }

  double nextValue(const double prevYVal, const double prevXVal, const double step)
  {
    double newVal{prevYVal};
    newVal += derivative(prevXVal, prevYVal) * step;

    return newVal;
  }

  double calcMeanError(const std::vector<std::pair<double, double>>& values, const int numSteps)
  {
    std::vector<double> differences(values.size());

    std::transform(std::begin(values), std::end(values), std::begin(differences), [](const std::pair<double, double> val) -> double
      {
        const auto truth = trueVal(val.first);
        return std::abs((val.second - truth) / truth);
      });

    double mean{std::accumulate(std::begin(differences), std::end(differences), 0.0) / (numSteps + 1)};

    mean = std::floor(mean * 1E6) / 1E6;

    return mean;
  }
}

double EulerOde::exEuler(int nb)
{
  const double step = 1.0 / nb;
  std::vector<std::pair<double, double>> fValues; // store results
  fValues.reserve(nb + 1);
  double currentXVal{0.0};
  fValues.emplace_back(std::make_pair(currentXVal, 1.0)); // given initial value

  for(int i = 1; i <= nb; ++i)
  {
    const double newYVal{eulerOdeHelpers::nextValue(fValues.at(i-1).second, currentXVal, step)};
    currentXVal += step;
    fValues.emplace_back(std::make_pair(currentXVal, newYVal));
  }

  const double meanError = eulerOdeHelpers::calcMeanError(fValues, nb);

  return meanError;
}
#endif // EULERMETHOD_H
