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
class BFSPathPlanner : public libpp_core::PathPlannerBase {
 public:
  BFSPathPlanner(PathPlannerParams params);

  void StepOnce() override;
  void StepUntilGoal() override;
  bool ComputePlan() override;
};
}  // namespace libpp

#endif /* SEARCH_BFS_HPP */
