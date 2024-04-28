/**
 * @file utest_node.cpp
 * @brief
 * @date 28-04-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include "libpp/core/node.hpp"

#include "gtest/gtest.h"

using namespace libpp_core;

TEST(NodeTest, InvalidNodeAttribute) {
  EXPECT_NO_THROW(
      NodeAttribute node_attribute(1, Dimension("x dimension", 0, 5, 1)););
}

TEST(NodeTest, ValidNodeAttribute) {
  EXPECT_THROW(
      NodeAttribute node_attribute(6, Dimension("x dimension", 0, 5, 1));
      , OutOfBoundError);
}