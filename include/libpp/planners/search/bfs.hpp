/**
 * @file bfs.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef SEARCH_BFS_HPP
#define SEARCH_BFS_HPP

#include "libpp/core/path_planner_base.hpp"

namespace libpp {
template <int Size>
class BFSPathPlanner : public libpp_core::PathPlannerBase<Size> {
 public:
  BFSPathPlanner(PathPlannerParams<Size> params)
      : PathPlannerBase<Size>(params) {}

  void StepOnce() override {}
  void StepUntilGoal() override  {}
  bool ComputePlan() override { return false; }
};
}  // namespace libpp

#endif /* SEARCH_BFS_HPP */
