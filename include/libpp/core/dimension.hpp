/**
 * @file dimension.hpp
 * @brief
 * @date 28-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_DIMENSION_HPP
#define CORE_DIMENSION_HPP

#include <memory>
#include <ostream>
#include <string>

#include <spdlog/fmt/ostr.h>

namespace libpp_core {
struct SearchBound {
  double lower_bound;
  double upper_bound;
};

class Dimension {
 public:
  Dimension(const std::string& name, const double& lower_bound,
            const double& upper_bound, const double& step,
            const std::string& unit = "");

  bool IsSearchBoundValid() const;
  bool IsValueWithinBound(const double& value) const;
  std::string GetName() const;
  std::string GetUnit() const;
  SearchBound GetBound() const;
  double GetStep() const;

  // override << operator
  friend std::ostream& operator<<(std::ostream& os, const Dimension& dim) {
    os << "Logging dimension " << dim.name_ << ": ";
    os << "Unit: " << dim.unit_ << ", ";
    os << "Lower bound: " << dim.bound_.lower_bound << ", ";
    os << "Upper bound: " << dim.bound_.upper_bound << ", ";
    os << "Step: " << dim.step_;
    return os;
  }

  // override == operator
  bool operator==(const Dimension& other) const;

 private:
  std::string name_;
  std::string unit_;
  SearchBound bound_;
  double step_;
};

template <int Size>
using Dimensions = std::array<Dimension, Size>;

}  // namespace libpp_core

#endif /* CORE_DIMENSION_HPP */
