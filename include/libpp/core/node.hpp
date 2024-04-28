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
struct NodeAttribute {
  NodeAttribute(const double& value, const Dimension& dimension);

  double GetValue() const;
  Dimension GetDimension();

 private:
  double value_;
  Dimension dimension_;
};

template <int Size>
using NodeAttributes = std::array<NodeAttribute, Size>;
// override the == operator for NodeAttributes
template <int Size>
bool operator==(const NodeAttributes<Size>& lhs,
                const NodeAttributes<Size>& rhs) {
  for (int i = 0; i < Size; ++i) {
    if (!(lhs[i].GetValue() == rhs[i].GetValue()) ||
        !(lhs[i].GetDimension() == rhs[i].GetDimension())) {
      return false;
    }
  }
  return true;
}

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
  NodeAttributes<Size> GetAttributes() const { return attributes_; }

 private:
  bool is_explored_;
  NodeAttributes<Size> attributes_;
};
}  // namespace libpp_core

#endif /* CORE_NODE_HPP */
