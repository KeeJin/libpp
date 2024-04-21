/**
 * @file bfs.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef SEARCH_BFS_HPP
#define SEARCH_BFS_HPP

#include "libpp/details/path_planner_base.hpp"

namespace libpp {
class BFSPathPlanner : public PathPlannerBase {
 public:
  BFSPathPlanner(const PathPlannerParams &params) : PathPlannerBase(params) {}

  void StepOnce() override {
    // Implement BFS algorithm
  }

  void StepUntilGoal() override {
    // Implement BFS algorithm
  }

  bool ComputePlan() override {
    // Implement BFS algorithm
    return false;
  }
};
}  // namespace libpp

#endif /* SEARCH_BFS_HPP */
