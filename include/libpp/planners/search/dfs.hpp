/**
 * @file dfs.hpp
 * @brief 
 * @date 11-05-2024
 * 
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#ifndef SEARCH_DFS_HPP
#define SEARCH_DFS_HPP

#include "spdlog/spdlog.h"

#include "libpp/core/path_planner_base.hpp"

using namespace libpp_core;
template <int Size>
class DFSPathPlanner : public PathPlannerBase<Size> {
    public:
    DFSPathPlanner(PathPlannerParams<Size> params)
        : PathPlannerBase<Size>(params) {}

    void StepOnce() override {}

    bool GetPlan(Path<Size>& plan) override {
        return false;
    }
};

#endif /* SEARCH_DFS_HPP */
