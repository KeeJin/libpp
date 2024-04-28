/**
 * @file utest_search_space.cpp
 * @brief
 * @date 20-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include <memory>

#include "gtest/gtest.h"

#include "libpp/core/search_space.hpp"

using namespace libpp_core;

TEST(SearchSpaceTest, CheckValidDimensionBounds) {
  Dimension x_dim = Dimension("valid x dimension", 0, 10, 1, "m");
  EXPECT_TRUE(x_dim.IsSearchBoundValid());
  std::cout << x_dim << std::endl;
}

TEST(SearchSpaceTest, CheckInvalidDimensionBounds) {
  Dimension x_dim = Dimension("invalid x dimension", 10, 0, 1);
  EXPECT_FALSE(x_dim.IsSearchBoundValid());
}

TEST(SearchSpaceTest, InitialiseInvalidSearchSpace) {
  Dimension x_dim = Dimension("valid x dimension", 0, 10, 1);
  ASSERT_TRUE(x_dim.IsSearchBoundValid());

  Dimension y_dim = Dimension("invalid y dimension", 55.0f, -5.5f, 0.1f);
  ASSERT_FALSE(y_dim.IsSearchBoundValid());

  Dimensions<2> dims = {x_dim, y_dim};

  // Expect exception to be thrown
  EXPECT_THROW(SearchSpace<2> space(dims), std::invalid_argument);
}

TEST(SearchSpaceTest, InitialiseValidSearchSpace) {
  Dimension x_dim = Dimension("valid x dimension", 0, 10, 1);
  Dimension y_dim = Dimension("valid y dimension", -5.0f, 55.5f, 0.1f);
  Dimension t_dim = Dimension("valid time dimension", 0.0, 60.0, 0.05);

  Dimensions<3> dims = {x_dim, y_dim, t_dim};
  try {
    SearchSpace<3> space(dims);
    std::cout << space << std::endl;
    EXPECT_EQ(space.GetDimensionSize(), 3);
  } catch (const std::invalid_argument& e) {
    FAIL() << "Exception thrown: " << e.what();
  }
}