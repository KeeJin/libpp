/**
 * @file dimension.cpp
 * @brief
 * @date 29-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include "libpp/core/dimension.hpp"

namespace libpp_core {
Dimension::Dimension(const std::string& name, const double& lower_bound,
                     const double& upper_bound, const double& step,
                     const std::string& unit)
    : name_(name),
      bound_({lower_bound, upper_bound}),
      step_(step),
      unit_(unit) {}

bool Dimension::IsSearchBoundValid() const {
  return bound_.lower_bound < bound_.upper_bound;
}

bool Dimension::IsValueWithinBound(const double& value) const {
  return value >= bound_.lower_bound && value <= bound_.upper_bound;
}
std::string Dimension::GetName() const { return name_; }

std::string Dimension::GetUnit() const { return unit_; }

SearchBound Dimension::GetBound() const { return bound_; }

double Dimension::GetStep() const { return step_; }

bool Dimension::operator==(const Dimension& other) const {
  return (name_ == other.name_ && unit_ == other.unit_ &&
          bound_.lower_bound == other.bound_.lower_bound &&
          bound_.upper_bound == other.bound_.upper_bound &&
          step_ == other.step_);
}
}  // namespace libpp_core