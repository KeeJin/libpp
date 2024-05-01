/**
 * @file edge.hpp
 * @brief
 * @date 01-05-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_EDGE_HPP
#define CORE_EDGE_HPP

#include <array>
#include <memory>

namespace libpp_core {
// forward declaration of template class Node
template <int Size>
class Node;

/**
 * @brief Undirected edge between two nodes
 *
 */
template <int Size>
class Edge {
 public:
  Edge(const std::array<std::shared_ptr<Node<Size>>, 2>& nodes) : nodes_(nodes) {}
  ~Edge() = default;

  void SetCost(const double& cost) { cost_ = cost; }
  double GetCost() const { return cost_; }
  std::array<std::shared_ptr<Node<Size>>, 2> GetAssociatedNodes() const {
    return nodes_;
  }

 private:
  
  std::array<std::shared_ptr<Node<Size>>, 2> nodes_;
  double cost_;
};
}  // namespace libpp_core

#endif /* CORE_EDGE_HPP */
