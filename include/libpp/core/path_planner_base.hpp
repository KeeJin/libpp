/**
 * @file path_planner_base.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_PATH_PLANNER_BASE_HPP
#define CORE_PATH_PLANNER_BASE_HPP

#include <vector>

#include "libpp/core/node.hpp"
#include "libpp/core/search_space.hpp"

namespace libpp_core {
template <int Size>
using Path = std::vector<NodeAttributes<Size>>;

/**
 * @brief Base class for path planner
 */
template <int Size>
class PathPlannerBase {
 public:
  template <int A>
  struct PathPlannerParams {
    Node<A> start_state;
    Node<A> goal_state;
    SearchSpace<A> search_space;
    bool VerifyParams() const { return true; }
  };
  enum class PlannerStatus {
    kStaging,
    kPlanning,
    kSucceeded,
    kFailed,
  };

 public:
  PathPlannerBase(PathPlannerParams<Size> params) : params_(params) {}
  virtual ~PathPlannerBase() = default;

  virtual void StepOnce() = 0;
  virtual void StepUntilGoal() = 0;
  virtual bool GetPlan(Path<Size>) = 0;

  PlannerStatus GetStatus() const { return status_; }

 protected:
  void UpdateStatus(const PlannerStatus& status) { status_ = status; }
  PathPlannerParams<Size> params_;

 private:
  PlannerStatus status_ = PlannerStatus::kStaging;
};
}  // namespace libpp_core

#endif /* CORE_PATH_PLANNER_BASE_HPP */
