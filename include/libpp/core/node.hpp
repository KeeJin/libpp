/**
 * @file node.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_NODE_HPP
#define CORE_NODE_HPP

#include "libpp/core/dimension.hpp"
#include "libpp/core/error_types.hpp"

namespace libpp_core {

struct NodeAttributeBase {
  virtual ~NodeAttributeBase() = default;
};

template <typename T>
struct NodeAttribute : public NodeAttributeBase {
  NodeAttribute(const T& value, const Dimension<T>& dimension)
      : value_(value), dimension_(dimension) {
    if (!dimension.IsValueWithinBound(value)) {
      throw OutOfBoundError("Value is not within bound");
    }
  }

 private:
  T value_;
  Dimension<T> dimension_;
};

template <int Size>
using NodeAttributes = std::array<std::unique_ptr<NodeAttributeBase>, Size>;

class NodeBase {
 public:
  virtual ~NodeBase() = default;
};

template <int Size>
class Node : public NodeBase {
 public:
  Node(NodeAttributes<Size> attributes)
      : is_explored_(false), attributes_(attributes) {}
  ~Node() = default;

  void MarkAsExplored() { is_explored_ = true; }

 private:
  bool is_explored_;
  NodeAttributes<Size> attributes_;
};
}  // namespace libpp_core

#endif /* CORE_NODE_HPP */
