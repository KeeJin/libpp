/**
 * @file utest_search_space.cpp
 * @brief
 * @date 20-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include <memory>

#include "libpp/core/search_space.hpp"

#include "gtest/gtest.h"

using namespace libpp_core;

TEST(SearchSpaceTest, CheckValidDimensionBounds) {
  std::unique_ptr<DimensionBase> x_dim =
      std::make_unique<Dimension<int>>("valid x dimension", 0, 10, -1);
  EXPECT_TRUE(x_dim->IsSearchBoundValid());
  std::cout << *(x_dim.get()) << std::endl;
}

TEST(SearchSpaceTest, CheckInvalidDimensionBounds) {
  std::unique_ptr<DimensionBase> x_dim =
      std::make_unique<Dimension<int>>("invalid x dimension", 10, 0, 1);
  EXPECT_FALSE(x_dim->IsSearchBoundValid());
}

TEST(SearchSpaceTest, InitialiseInvalidSearchSpace) {
  std::unique_ptr<DimensionBase> x_dim =
      std::make_unique<Dimension<int>>("valid x dimension", 0, 10, 1);
  ASSERT_TRUE(x_dim->IsSearchBoundValid());

  std::unique_ptr<DimensionBase> y_dim = std::make_unique<Dimension<float>>(
      "invalid y dimension", 55.0f, -5.5f, 0.1f);
  ASSERT_FALSE(y_dim->IsSearchBoundValid());

  Dimensions<2> dims = {std::move(x_dim), std::move(y_dim)};

  // Expect exception to be thrown
  EXPECT_THROW(SearchSpace<2> space(std::move(dims)), std::invalid_argument);
}

TEST(SearchSpaceTest, InitialiseValidSearchSpace) {
  std::unique_ptr<DimensionBase> x_dim =
      std::make_unique<Dimension<int>>("valid x dimension", 0, 10, 1);
  std::unique_ptr<DimensionBase> y_dim = std::make_unique<Dimension<float>>(
      "valid y dimension", -5.0f, 55.5f, 0.1f);
  std::unique_ptr<DimensionBase> t_dim = std::make_unique<Dimension<double>>(
      "valid time dimension", 0.0, 60.0, 0.05);

  std::array<std::unique_ptr<DimensionBase>, 3> dims = {
      std::move(x_dim), std::move(y_dim), std::move(t_dim)};
  try {
    SearchSpace<3> space(std::move(dims));
    std::cout << space << std::endl;
    EXPECT_EQ(space.GetDimensionSize(), 3);
  } catch (const std::invalid_argument& e) {
    FAIL() << "Exception thrown: " << e.what();
  }
}