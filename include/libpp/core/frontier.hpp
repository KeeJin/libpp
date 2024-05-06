/**
 * @file frontier.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_FRONTIER_HPP
#define CORE_FRONTIER_HPP

#include <queue>
#include <memory>

#include "spdlog/spdlog.h"

#include "libpp/core/node.hpp"

namespace libpp_core {
template <int Size>
class Frontier {
 public:
  Frontier(std::shared_ptr<Node<Size>> start_node) {
    frontier_.push(start_node);
    SPDLOG_DEBUG("Frontier initialized with start node");
  }
  void EnqueueNode(std::shared_ptr<Node<Size>> node) {
    SPDLOG_DEBUG("Enqueueing node to frontier:");
    for (const auto& attr : node->GetAttributes()) {
      SPDLOG_DEBUG("  {}", attr);
    }
    frontier_.push(node);
  }
  std::shared_ptr<Node<Size>> DequeueNode() {
    if (frontier_.empty()) {
      SPDLOG_DEBUG("Frontier is empty");
      return std::shared_ptr<Node<Size>>();
    }
    SPDLOG_DEBUG("Dequeueing node from frontier");
    auto node = frontier_.front();
    for (const auto& attr : node->GetAttributes()) {
      SPDLOG_DEBUG("  {}", attr);
    }
    frontier_.pop();
    return node;
  }

 private:
  std::queue<std::shared_ptr<Node<Size>>> frontier_;
};
}  // namespace libpp_core

#endif /* CORE_FRONTIER_HPP */
