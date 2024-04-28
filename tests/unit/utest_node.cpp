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
  EXPECT_NO_THROW(NodeAttribute<int> node_attribute(
                      1, Dimension<int>("x dimension", 0, 5, std::nullopt)););
}

TEST(NodeTest, ValidNodeAttribute) {
  EXPECT_THROW(NodeAttribute<int> node_attribute(
                   6, Dimension<int>("x dimension", 0, 5, std::nullopt));
               , OutOfBoundError);
}