/**
 * @file path_planner_base.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef DETAILS_PATH_PLANNER_BASE_HPP
#define DETAILS_PATH_PLANNER_BASE_HPP

#include "libpp/details/node.hpp"

namespace libpp {
class PathPlannerBase {
 public:
  struct PathPlannerParams {
    Node start_state;
    Node goal_state;
  };
  enum class PlannerStatus {
    kStaging,
    kPlanning,
    kSucceeded,
    kFailed,
  };

 public:
  PathPlannerBase(const PathPlannerParams& params) : params_(params) {}
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
}  // namespace libpp

#endif /* DETAILS_PATH_PLANNER_BASE_HPP */
