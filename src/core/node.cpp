/**
 * @file node.cpp
 * @brief
 * @date 29-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include "libpp/core/node.hpp"

namespace libpp_core {
NodeAttribute::NodeAttribute(const double& value, const Dimension& dimension)
    : value_(value), dimension_(dimension) {
  if (!dimension.IsValueWithinBound(value)) {
    throw OutOfBoundError("Value is not within bound");
  }
}

double NodeAttribute::GetValue() const { return value_; }

Dimension NodeAttribute::GetDimension() { return dimension_; }

}  // namespace libpp_core