/**
 * @file test_search_space.cpp
 * @brief
 * @date 29-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include "spdlog/spdlog.h"

#include "libpp/core/search_space.hpp"

using namespace libpp_core;

int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("Testing SearchSpace.");

  auto x_dim = Dimension("x dimension", 0, 5, 1);
  auto y_dim = Dimension("y dimension", 0, 5, 1);
  auto z_dim = Dimension("z dimension", 0, 5, 1);
  Dimensions<3> dims = {x_dim, y_dim, z_dim};
  for (const auto& dim : dims) {
    spdlog::debug("Dimension: {}", dim);
  }

  SearchSpace<3> search_space(dims);
  spdlog::debug("SearchSpace created: {}", search_space);

  spdlog::info("Test complete.");
  return 0;
}