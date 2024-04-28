/**
 * @file path_planner_base.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_PATH_PLANNER_BASE_HPP
#define CORE_PATH_PLANNER_BASE_HPP

#include "libpp/core/node.hpp"

namespace libpp_core {
class PathPlannerBase {
 public:
  struct PathPlannerParams {
    std::unique_ptr<NodeBase> start_state;
    std::unique_ptr<NodeBase> goal_state;
  };
  enum class PlannerStatus {
    kStaging,
    kPlanning,
    kSucceeded,
    kFailed,
  };

 public:
  PathPlannerBase(PathPlannerParams params) : params_(std::move(params)) {}
  virtual ~PathPlannerBase() = default;

  virtual void StepOnce() = 0;
  virtual void StepUntilGoal() = 0;
  virtual bool ComputePlan() = 0;

  PlannerStatus GetStatus() const { return status_; }

 protected:
  void UpdateStatus(const PlannerStatus& status) { status_ = status; }
  PathPlannerParams params_;

 private:
  PlannerStatus status_ = PlannerStatus::kStaging;
};
}  // namespace libpp_core

#endif /* CORE_PATH_PLANNER_BASE_HPP */
