/**
 * @file search_space.hpp
 * @brief
 * @date 20-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef BASE_SEARCH_SPACE_HPP
#define BASE_SEARCH_SPACE_HPP

#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <iostream>

namespace libpp {
template <typename T>
struct SearchBound {
  T lower_bound;
  T upper_bound;
};

struct DimensionBase {
  virtual bool IsSearchBoundValid() const = 0;
  std::string name;
  
  protected:
  virtual std::ostream& LogInfo(std::ostream& os) const {
    os << "Base class logging dimension" << std::endl;
    return os;
  }
  friend std::ostream& operator<<(std::ostream& os, const DimensionBase& parent) {
    return(parent.LogInfo(os));
  }
};

template <typename T>
struct Dimension : public DimensionBase {
  bool IsSearchBoundValid() const override {
    return bound.lower_bound < bound.upper_bound;
  }
  std::string name;
  SearchBound<T> bound;
  std::optional<T> step;
  std::ostream& LogInfo(std::ostream& os) const override {
    os << "Logging dimension " << name << ": ";
    os << "Lower bound: " << bound.lower_bound << ", ";
    os << "Upper bound: " << bound.upper_bound << ", ";
    if (step.has_value()) {
      os << "Step: " << step.value() << std::endl;
    } else {
      os << "Step: N/A" << std::endl;
    }
    return os;
  }
};

struct SearchSpace {
  int GetDimensionSize() const { return dims.size(); }
  bool AddDimension(std::shared_ptr<DimensionBase> dim) {
    if (!dim->IsSearchBoundValid()) {
      return false;
    }
    std::cout << "Adding dimension: " << dim->name << std::endl;
    dims.push_back(dim);
    return true;
  }
  std::vector<std::shared_ptr<DimensionBase>> dims;

  // override << operator to log the search space
  friend std::ostream& operator<<(std::ostream& os, const SearchSpace& space) {
    os << "Logging SearchSpace dimensions: \n";
    for (const auto& dim : space.dims) {
      os << *(dim.get());
    }
    os << "-----------------------------" << std::endl;
    return os;
  }
};
}  // namespace libpp

#endif /* BASE_SEARCH_SPACE_HPP */
