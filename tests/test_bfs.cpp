/**
 * @file test_bfs.cpp
 * @brief
 * @date 05-05-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

// set logging level
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include "spdlog/spdlog.h"

#include "libpp/planners/search/bfs.hpp"
#include "libpp/core/dimension.hpp"
#include "libpp/core/node.hpp"

using namespace libpp;

int main() {
  spdlog::set_level(spdlog::level::debug);
  Dimension x_dim = Dimension("x", 0, 5, 1);
  Dimension y_dim = Dimension("y", 0, 5, 1);
  Dimensions<2> dims = {x_dim, y_dim};
  auto start_state =
      NodeAttributes<2>{NodeAttribute(1, x_dim), NodeAttribute(1, y_dim)};
  auto goal_state =
      NodeAttributes<2>{NodeAttribute(5, x_dim), NodeAttribute(5, y_dim)};
  PathPlannerParams<2> params = {start_state, goal_state, dims};

  try {
    BFSPathPlanner<2> bfs(params);
    bfs.StepUntilGoal();
    // while (bfs.GetStatus() != PathPlannerBase<2>::PlannerStatus::kSucceeded &&
    //        bfs.GetStatus() != PathPlannerBase<2>::PlannerStatus::kFailed) {
    //   bfs.StepOnce();
    // }
    switch (bfs.GetStatus()) {
      case PathPlannerBase<2>::PlannerStatus::kSucceeded: {
        SPDLOG_INFO("BFS planner succeeded");
        Path<2> path;
        bool res = bfs.GetPlan(path);
        SPDLOG_INFO("Path:");
        while (!path.empty()) {
          auto attrs = path.top();
          SPDLOG_INFO("[{}, {}]", attrs[0].GetValue(), attrs[1].GetValue());
          path.pop();
        }

        break;
      }
      case PathPlannerBase<2>::PlannerStatus::kFailed:
        SPDLOG_INFO("BFS planner failed");
        break;

      default:
        SPDLOG_INFO("BFS planner is still not done yet");
        break;
    }
  } catch (const std::runtime_error& e) {
    SPDLOG_ERROR("Failed to construct BFS planner: {}", e.what());
  }
}