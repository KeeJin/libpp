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

#include "fmt/ostream.h"

namespace libpp_core {
struct SearchBound {
  double lower_bound;
  double upper_bound;
};

class Dimension {
 public:
  Dimension(const std::string& name, const double& lower_bound,
            const double& upper_bound, const double& step,
            const std::string& unit = "")
      : name_(name),
        bound_({lower_bound, upper_bound}),
        step_(step),
        unit_(unit) {}
  bool IsSearchBoundValid() const {
    return bound_.lower_bound < bound_.upper_bound;
  }
  bool IsValueWithinBound(const double& value) const {
    return value >= bound_.lower_bound && value <= bound_.upper_bound;
  }
  std::string GetName() const { return name_; }
  std::string GetUnit() const { return unit_; }
  SearchBound GetBound() const { return bound_; }
  double GetStep() const { return step_; }

  // override << operator
  friend std::ostream& operator<<(std::ostream& os, const Dimension& dim) {
    os << "Logging dimension " << dim.name_ << ": ";
    os << "Unit: " << dim.unit_ << ", ";
    os << "Lower bound: " << dim.bound_.lower_bound << ", ";
    os << "Upper bound: " << dim.bound_.upper_bound << ", ";
    os << "Step: " << dim.step_ << std::endl;
    return os;
  }

  // override == operator
  bool operator==(const Dimension& other) const {
    return (name_ == other.name_ && unit_ == other.unit_ &&
            bound_.lower_bound == other.bound_.lower_bound &&
            bound_.upper_bound == other.bound_.upper_bound &&
            step_ == other.step_);
  }

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
