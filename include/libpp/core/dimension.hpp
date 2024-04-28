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
#include <optional>
#include <ostream>
#include <string>

namespace libpp_core {
template <typename T>
struct SearchBound {
  T lower_bound;
  T upper_bound;
};

class DimensionBase {
 public:
  virtual ~DimensionBase() = default;

  virtual bool IsSearchBoundValid() const = 0;
  std::string name;

 protected:
  virtual std::ostream& LogInfo(std::ostream& os) const {
    os << "Base class logging dimension" << std::endl;
    return os;
  }
  friend std::ostream& operator<<(std::ostream& os,
                                  const DimensionBase& parent) {
    return (parent.LogInfo(os));
  }
};

template <typename T>
class Dimension : public DimensionBase {
 public:
  Dimension(std::string name, T lower_bound, T upper_bound,
            std::optional<T> step)
      : name_(name), bound_({lower_bound, upper_bound}), step_(step) {}
  bool IsSearchBoundValid() const override {
    return bound_.lower_bound < bound_.upper_bound;
  }
  bool IsValueWithinBound(const T& value) const {
    return value >= bound_.lower_bound && value <= bound_.upper_bound;
  }

 protected:
  std::ostream& LogInfo(std::ostream& os) const override {
    os << "Logging dimension " << name_ << ": ";
    os << "Lower bound: " << bound_.lower_bound << ", ";
    os << "Upper bound: " << bound_.upper_bound << ", ";
    if (step_.has_value()) {
      os << "Step: " << step_.value() << std::endl;
    } else {
      os << "Step: N/A" << std::endl;
    }
    return os;
  }

 private:
  std::string name_;
  SearchBound<T> bound_;
  std::optional<T> step_;
};

// Note: we use unique_ptr to prevent modifying the dimension after it is
// passed into the search space.
template <int Size>
using Dimensions = std::array<std::unique_ptr<DimensionBase>, Size>;

}  // namespace libpp_core

#endif /* CORE_DIMENSION_HPP */
