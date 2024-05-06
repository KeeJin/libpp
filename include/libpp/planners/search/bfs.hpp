/**
 * @file bfs.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef SEARCH_BFS_HPP
#define SEARCH_BFS_HPP

#include "spdlog/spdlog.h"

#include "libpp/core/path_planner_base.hpp"

using namespace libpp_core;
namespace libpp {
template <int Size>
class BFSPathPlanner : public PathPlannerBase<Size> {
 public:
  BFSPathPlanner(PathPlannerParams<Size> params)
      : PathPlannerBase<Size>(params) {}

  void StepOnce() override {
    if (this->status_ == PathPlannerBase<Size>::PlannerStatus::kSucceeded ||
        this->status_ == PathPlannerBase<Size>::PlannerStatus::kFailed) {
      SPDLOG_INFO("Planner has already succeeded or failed");
      return;
    }
    auto node = this->frontier_->DequeueNode();
    if (!node) {
      SPDLOG_INFO(
          "Frontier is empty but goal not reached. This means the planner has "
          "failed");
      this->status_ = PathPlannerBase<Size>::PlannerStatus::kFailed;
      return;
    }
    node->MarkAsExplored();
    auto unexplored_neighbors = node->GetUnexploredNeighbours();
    for (const auto& neighbor : unexplored_neighbors) {
      neighbor->SetParent(node);
      this->frontier_->EnqueueNode(neighbor);
    }
    if (node->GetAttributes() == this->params_.goal_state) {
      SPDLOG_INFO("Goal reached");
      this->status_ = PathPlannerBase<Size>::PlannerStatus::kSucceeded;
      return;
    }
  }
  bool GetPlan(Path<Size>& plan) override {
    if (this->status_ != PathPlannerBase<Size>::PlannerStatus::kSucceeded) {
      SPDLOG_INFO("Planner has not succeeded yet");
      return false;
    }
    auto node = this->search_space_->GetNode(this->params_.goal_state);
    if (!node) {
      SPDLOG_ERROR("Goal node not found in search space");
      return false;
    }
    while (node->GetAttributes() != this->params_.start_state) {
      plan.push(node->GetAttributes());
      if (node->GetAttributes() == this->params_.start_state) {
        break;
      }
      node = node->GetParent();
      if (!node) {
        SPDLOG_ERROR("Parent node not found");
        return false;
      }
    }
    return true;
  }
};
}  // namespace libpp

#endif /* SEARCH_BFS_HPP */
