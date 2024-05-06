/**
 * @file path_planner_base.hpp
 * @brief
 * @date 21-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef CORE_PATH_PLANNER_BASE_HPP
#define CORE_PATH_PLANNER_BASE_HPP

#include <stack>

#include "libpp/core/node.hpp"
#include "libpp/core/search_space.hpp"
#include "libpp/core/frontier.hpp"

namespace libpp_core {
template <int Size>
using Path = std::stack<NodeAttributes<Size>>;

template <int Size>
struct PathPlannerParams {
  NodeAttributes<Size> start_state;
  NodeAttributes<Size> goal_state;
  Dimensions<Size> dims;
  bool VerifyParams() const { return true; }
};

/**
 * @brief Base class for path planner
 */
template <int Size>
class PathPlannerBase {
 public:
  enum class PlannerStatus {
    kStaging,
    kPlanning,
    kSucceeded,
    kFailed,
  };

 public:
  PathPlannerBase(PathPlannerParams<Size> params) : params_(params) {
    if (!params.VerifyParams()) {
      throw std::runtime_error("Invalid path planner parameters");
    }
    try {
      ConstructGraph();
    } catch (const std::runtime_error& e) {
      throw std::runtime_error("Failed to construct graph");
    }
  }
  virtual ~PathPlannerBase() = default;

  /**
   * @brief It is the derived class responsibility to update the status
   *
   */
  virtual void StepOnce() = 0;
  void StepUntilGoal() {
    while (!(status_ == PlannerStatus::kFailed ||
             status_ == PlannerStatus::kSucceeded)) {
      StepOnce();
    }
  }
  virtual bool GetPlan(Path<Size>& plan) = 0;

  PlannerStatus GetStatus() const { return status_; }

 protected:
  void UpdateStatus(const PlannerStatus& status) { status_ = status; }
  PathPlannerParams<Size> params_;
  std::unique_ptr<SearchSpace<Size>> search_space_;
  std::unique_ptr<Frontier<Size>> frontier_;
  PlannerStatus status_ = PlannerStatus::kStaging;

 private:
  void ConstructGraph() {
    try {
      search_space_ = std::make_unique<SearchSpace<Size>>(params_.dims);
    } catch (const std::invalid_argument& e) {
      throw std::runtime_error("Invalid search space dimensions");
    }
    NodeAttributes<Size> attributes;
    // Initialize all dimensions to lower bound
    for (int i = 0; i < Size; ++i) {
      auto dim = params_.dims[i];
      attributes[i] = NodeAttribute(dim.GetBound().lower_bound, dim);
    }

    // Add all possible nodes to the search space
    SPDLOG_INFO("Adding all possible nodes to search space");
    SearchSpaceIterator(attributes, 0);
    SPDLOG_INFO("Search space constructed with {} nodes",
                search_space_->GetNodes().size());

    // Establish connections between nodes
    for (auto node : search_space_->GetNodes()) {
      auto attributes = node->GetAttributes();
      // iterate through all dimensions
      for (int i = 0; i < Size; ++i) {
        NodeAttributes<Size> new_attributes = attributes;
        // previous step
        new_attributes[i].SetValue(attributes[i].GetValue() -
                                   params_.dims[i].GetStep());
        auto prev_node = search_space_->GetNode(new_attributes);
        if (prev_node) {
          node->AddNeighbor(prev_node);
        }
        // next step
        new_attributes = attributes;
        new_attributes[i].SetValue(attributes[i].GetValue() +
                                   params_.dims[i].GetStep());
        auto next_node = search_space_->GetNode(new_attributes);
        if (next_node) {
          node->AddNeighbor(next_node);
        }
      }
    }
    SPDLOG_INFO("Connections established between nodes");

    // Initialize frontier
    auto start_node = search_space_->GetNode(params_.start_state);
    if (!start_node) {
      throw std::runtime_error("Start node not found in search space");
    }
    frontier_ = std::make_unique<Frontier<Size>>(start_node);
  }

  void SearchSpaceIterator(NodeAttributes<Size> attributes, int dimension = 0) {
    if (dimension == Size) {
      // This implies we have reached the end of the dimensions
      SPDLOG_DEBUG("Node found in search space:");
      for (const auto& attr : attributes) {
        SPDLOG_DEBUG("  {}", attr);
      }
      SPDLOG_DEBUG("-------------------------");
      search_space_->AddNode(std::make_shared<Node<Size>>(attributes));
      return;
    }

    auto dim = params_.dims[dimension];
    for (float i = dim.GetBound().lower_bound; i <= dim.GetBound().upper_bound;
         i += dim.GetStep()) {
      attributes[dimension].SetValue(i);
      SearchSpaceIterator(attributes, dimension + 1);
    }
  }
};
}  // namespace libpp_core

#endif /* CORE_PATH_PLANNER_BASE_HPP */
