/**
 * @file bfs.cpp
 * @brief
 * @date 28-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include "libpp/planners/search/bfs.hpp"

namespace libpp {
BFSPathPlanner::BFSPathPlanner(PathPlannerParams params)
    : PathPlannerBase(std::move(params)) {}

void BFSPathPlanner::StepOnce() {
  // Implement BFS algorithm
}

void BFSPathPlanner::StepUntilGoal() {
  // Implement BFS algorithm
}

bool BFSPathPlanner::ComputePlan() {
  // Implement BFS algorithm
  return false;
}
}  // namespace libpp