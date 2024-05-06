/**
 * @file utest_dimension.cpp
 * @brief 
 * @date 06-05-2024
 * 
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include <memory>

#include "gtest/gtest.h"

#include "libpp/core/search_space.hpp"

using namespace libpp_core;

TEST(DimensionTest, CheckValidDimensionBounds) {
  Dimension x_dim = Dimension("valid x dimension", 0, 10, 1, "m");
  EXPECT_TRUE(x_dim.IsSearchBoundValid());
  std::cout << x_dim << std::endl;
}

TEST(DimensionTest, CheckInvalidDimensionBounds) {
  Dimension x_dim = Dimension("invalid x dimension", 10, 0, 1);
  EXPECT_FALSE(x_dim.IsSearchBoundValid());
}