/**
 * @file node.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_NODE_HPP
#define CORE_NODE_HPP

#include <array>
#include <unordered_map>
#include <memory>

#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>

#include "libpp/core/dimension.hpp"
#include "libpp/core/edge.hpp"
#include "libpp/core/error_types.hpp"

namespace libpp_core {
struct NodeAttribute {
  NodeAttribute();
  NodeAttribute(const double& value, const Dimension& dimension);

  bool SetValue(const double& value);
  double GetValue() const;
  Dimension GetDimension() const;

  bool operator==(const NodeAttribute& other) const {
    return value_ == other.value_ && dimension_ == other.dimension_;
  }
  bool operator!=(const NodeAttribute& other) const {
    return !(*this == other);
  }
  friend std::ostream& operator<<(std::ostream& os,
                                  const NodeAttribute& attribute) {
    os << attribute.GetValue() << " ";
    os << attribute.GetDimension();
    return os;
  }

 private:
  double value_;
  Dimension dimension_;
};

template <int Size>
using NodeAttributes = std::array<NodeAttribute, Size>;

// override the == operator for NodeAttributes

template <int Size>
class Node : public std::enable_shared_from_this<Node<Size>> {
 public:
  Node(NodeAttributes<Size> attributes)
      : is_explored_(false), attributes_(attributes) {}
  ~Node() = default;

  void MarkAsExplored() { is_explored_ = true; }
  bool IsExplored() const { return is_explored_; }
  NodeAttributes<Size> GetAttributes() const { return attributes_; }

  void SetParent(std::shared_ptr<Node<Size>> parent) { parent_ = parent; }
  std::shared_ptr<Node<Size>> GetParent() const { return parent_; }

  void AddNeighbor(std::shared_ptr<Node<Size>> node) {
    if (IsNeighbour(node)) {
      // SPDLOG_WARN("Node is already a neighbor");
      return;
    }
    auto nodes = std::array<std::shared_ptr<Node<Size>>, 2>{
        this->shared_from_this(), node};
    auto edge = std::make_shared<Edge<Size>>(nodes);
    AddNeighbor(edge, node);
    node->AddNeighbor(edge, this->shared_from_this());
  }

  void AddNeighbor(std::shared_ptr<Edge<Size>> edge,
                   std::shared_ptr<Node<Size>> node) {
    if (IsNeighbour(node)) {
      // SPDLOG_WARN("Node is already a neighbor");
      return;
    }
    if (neighbours_.find(edge) != neighbours_.end()) {
      throw libpp_core::DuplicateEdgeError(
          "Edge is already a neighbor to the node");
    }
    neighbours_.insert({edge, node});
    SPDLOG_TRACE("Added neighbor");
  }

  bool IsNeighbour(std::shared_ptr<Node<Size>> node) const {
    for (const auto& neighbor : neighbours_) {
      if (neighbor.second->GetAttributes() == node->GetAttributes()) {
        return true;
      }
    }
    return false;
  }

  std::vector<std::shared_ptr<Node<Size>>> GetNeighbours() const {
    // O(n) time complexity
    std::vector<std::shared_ptr<Node<Size>>> nodes;
    for (const auto& neighbor : neighbours_) {
      nodes.push_back(neighbor.second);
    }
    return nodes;
  }

  std::vector<std::shared_ptr<Node<Size>>> GetUnexploredNeighbours() const {
    // O(n) time complexity
    std::vector<std::shared_ptr<Node<Size>>> nodes;
    for (const auto& neighbor : neighbours_) {
      if (!neighbor.second->IsExplored()) {
        nodes.push_back(neighbor.second);
      }
    }
    return nodes;
  }

  std::vector<std::shared_ptr<Edge<Size>>> GetEdges() const {
    // O(n) time complexity
    std::vector<std::shared_ptr<Edge<Size>>> edges;
    for (const auto& neighbor : neighbours_) {
      edges.push_back(neighbor.first);
    }
    return edges;
  }

  std::shared_ptr<Node<Size>> GetNeighborByEdge(
      std::shared_ptr<Edge<Size>> edge) const {
    if (neighbours_.find(edge) == neighbours_.end()) {
      return std::shared_ptr<Node<Size>>();  // TODO: check if this works as
                                             // intended
    }
    SPDLOG_WARN("No neighbor found by edge");
    return neighbours_.at(edge);
  }

  std::shared_ptr<Edge<Size>> GetEdgeToNeighbour(
      std::shared_ptr<Node<Size>> node) const {
    for (const auto& neighbor : neighbours_) {
      if (neighbor.second->GetAttributes() == node->GetAttributes()) {
        return neighbor.first;
      }
    }
    SPDLOG_WARN("No edge found to neighbor");
    return std::shared_ptr<Edge<Size>>();  // TODO: check if this works as
                                           // intended
  }

 private:
  bool is_explored_;
  NodeAttributes<Size> attributes_;
  std::unordered_map<std::shared_ptr<Edge<Size>>, std::shared_ptr<Node<Size>>>
      neighbours_;
  std::shared_ptr<Node<Size>> parent_;

  // std::unordered_set<std::shared_ptr<Edge<Size>>> edges_;
  // std::unordered_set<std::shared_ptr<Node<Size>>> nodes_;
};

}  // namespace libpp_core

#endif /* CORE_NODE_HPP */
