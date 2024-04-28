/**
 * @file search_space.hpp
 * @brief
 * @date 20-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_SEARCH_SPACE_HPP
#define CORE_SEARCH_SPACE_HPP

#include <array>
#include <memory>

#include "libpp/core/dimension.hpp"

namespace libpp_core {
template <int Size>
class SearchSpace {
  public:
  SearchSpace(Dimensions<Size> dims) {
    for (const auto& dim : dims) {
      if (!dim->IsSearchBoundValid()) {
        throw std::invalid_argument("Invalid search bound");
      }
    }
    dims_ = std::move(dims);
  }
  int GetDimensionSize() const { return dims_.size(); }

  private:
  Dimensions<Size> dims_;

  // override << operator to log the search space
  friend std::ostream& operator<<(std::ostream& os, const SearchSpace& space) {
    os << "Logging SearchSpace dimensions: \n";
    for (const auto& dim : space.dims_) {
      os << *(dim.get());
    }
    os << "-----------------------------" << std::endl;
    return os;
  }
};
}  // namespace libpp_core

#endif /* CORE_SEARCH_SPACE_HPP */
