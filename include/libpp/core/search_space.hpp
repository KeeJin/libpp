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
#include <unordered_set>

#include <spdlog/fmt/ostr.h>

#include "libpp/core/dimension.hpp"
#include "libpp/core/node.hpp"

namespace libpp_core {
template <int Size>
class SearchSpace {
 public:
  SearchSpace(Dimensions<Size> dims) : dims_(dims) {
    for (const auto& dim : dims) {
      if (!dim.IsSearchBoundValid()) {
        throw std::invalid_argument("Invalid search bound");
      }
    }
  }

  int GetDimensionSize() const { return dims_.size(); }
  bool AddNode(std::shared_ptr<Node<Size>> node) {
    if (IsNodeWithinSearchSpace(node) && !IsNodeAdded(node->GetAttributes())) {
      nodes_.insert(node);
      return true;
    }
    return false;
  }
  std::shared_ptr<Node<Size>> GetNode(NodeAttributes<Size> attributes) const {
    for (const auto& node : nodes_) {
      if (node->GetAttributes() == attributes) {
        return node;
      }
    }
    return std::shared_ptr<Node<Size>>();
  }
  std::unordered_set<std::shared_ptr<Node<Size>>> GetNodes() const {
    return nodes_;
  }
  bool IsNodeWithinSearchSpace(std::shared_ptr<Node<Size>> node) const {
    for (int i = 0; i < Size; ++i) {
      if (!(dims_[i] == (node->GetAttributes()[i].GetDimension()))) {
        return false;
      }
    }
    return true;
  }
  bool IsNodeAdded(NodeAttributes<Size> attributes) const {
    for (const auto& node : nodes_) {
      if (node->GetAttributes() == attributes) {
        return true;
      }
    }
    return false;
  }

  // override << operator to log the search space
  friend std::ostream& operator<<(std::ostream& os,
                                  const SearchSpace& search_space) {
    os << "Logging SearchSpace dimensions: \n";
    for (const auto& dim : search_space.dims_) {
      os << dim;
    }
    os << "-----------------------------" << std::endl;
    return os;
  }

 private:
  Dimensions<Size> dims_;
  std::unordered_set<std::shared_ptr<Node<Size>>> nodes_;
};
}  // namespace libpp_core

#endif /* CORE_SEARCH_SPACE_HPP */
