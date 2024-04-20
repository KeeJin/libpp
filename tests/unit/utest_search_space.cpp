/**
 * @file utest_search_space.cpp
 * @brief 
 * @date 20-04-2024
 * 
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include <memory>

#include "libpp/details/search_space.hpp"

#include "gtest/gtest.h"

using namespace libpp;

TEST(SearchSpaceTest, CheckValidDimensionBounds) {
  std::shared_ptr<DimensionBase> x_dim = std::make_shared<Dimension<int>>();
  x_dim->name = "x dimension";
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->bound.lower_bound = 0;
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->bound.upper_bound = 10;
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->step = 1;

  EXPECT_TRUE(x_dim->IsSearchBoundValid());
  std::cout << x_dim << std::endl;
}

TEST(SearchSpaceTest, CheckInvalidDimensionBounds) {
  std::shared_ptr<DimensionBase> x_dim = std::make_shared<Dimension<int>>();
  x_dim->name = "x dimension";
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->bound.lower_bound = 10;
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->bound.upper_bound = 0;
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->step = 1;

  EXPECT_FALSE(x_dim->IsSearchBoundValid());
}

TEST(SearchSpaceTest, AddDimension) {
  SearchSpace space;
  std::shared_ptr<DimensionBase> x_dim = std::make_shared<Dimension<int>>();
  x_dim->name = "x dimension";
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->bound.lower_bound = 0;
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->bound.upper_bound = 10;
  std::dynamic_pointer_cast<Dimension<int>>(x_dim)->step = 1;
  
  std::shared_ptr<DimensionBase> y_dim = std::make_shared<Dimension<float>>();
  y_dim->name = "y dimension";
  std::dynamic_pointer_cast<Dimension<float>>(y_dim)->bound.lower_bound = -5.0f;
  std::dynamic_pointer_cast<Dimension<float>>(y_dim)->bound.upper_bound = 55.5f;
  std::dynamic_pointer_cast<Dimension<float>>(y_dim)->step = 0.1f;

  std::shared_ptr<DimensionBase> t_dim = std::make_shared<Dimension<double>>();
  t_dim->name = "time dimension";
  std::dynamic_pointer_cast<Dimension<double>>(t_dim)->bound.lower_bound = 0.0;
  std::dynamic_pointer_cast<Dimension<double>>(t_dim)->bound.upper_bound = 60.0;
  std::dynamic_pointer_cast<Dimension<double>>(t_dim)->step = 0.05;

  EXPECT_TRUE(space.AddDimension(x_dim));
  EXPECT_TRUE(space.AddDimension(y_dim));
  EXPECT_TRUE(space.AddDimension(t_dim));
  std::cout << space << std::endl;
  EXPECT_EQ(space.GetDimensionSize(), 3);
}