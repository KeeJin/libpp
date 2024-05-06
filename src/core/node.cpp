/**
 * @file node.cpp
 * @brief
 * @date 29-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include "libpp/core/node.hpp"

namespace libpp_core {
NodeAttribute::NodeAttribute() : value_(0), dimension_(Dimension("default", 0.0, 0.0, 0.0)) {}

NodeAttribute::NodeAttribute(const double& value, const Dimension& dimension)
    : value_(value), dimension_(dimension) {
  if (!dimension_.IsValueWithinBound(value_)) {
    throw OutOfBoundError("Value is not within bound");
  }
}

bool NodeAttribute::SetValue(const double& value) {
  if (!dimension_.IsValueWithinBound(value)) {
    return false;
  }
  value_ = value;
  return true;
}

double NodeAttribute::GetValue() const { return value_; }

Dimension NodeAttribute::GetDimension() const { return dimension_; }

}  // namespace libpp_core