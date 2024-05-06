/**
 * @file utest_frontier.cpp
 * @brief
 * @date 06-05-2024
 *
 * @copyright Copyright (c) 2024 Cheo Kee Jin.
 */

#include <memory>

#include "gtest/gtest.h"

#include "libpp/core/frontier.hpp"

using namespace libpp_core;

struct FrontierTest : testing::Test {
  FrontierTest() {
    Dimension x_dim = Dimension("x dimension", 0, 10, 1);
    Dimension y_dim = Dimension("y dimension", 0, 10, 1);
    NodeAttribute node_attribute_1(1, x_dim);
    NodeAttribute node_attribute_2(4, y_dim);
    NodeAttribute node_attribute_3(2, x_dim);
    NodeAttribute node_attribute_4(6, y_dim);

    start_node = std::make_shared<Node<2>>(
        (NodeAttributes<2>){node_attribute_1, node_attribute_2});
    node1 = std::make_shared<Node<2>>(
        (NodeAttributes<2>){node_attribute_1, node_attribute_4});
    node2 = std::make_shared<Node<2>>(
        (NodeAttributes<2>){node_attribute_3, node_attribute_2});
    node3 = std::make_shared<Node<2>>(
        (NodeAttributes<2>){node_attribute_3, node_attribute_4});
  }

  std::shared_ptr<Node<2>> start_node;
  std::shared_ptr<Node<2>> node1;
  std::shared_ptr<Node<2>> node2;
  std::shared_ptr<Node<2>> node3;
};

TEST_F(FrontierTest, EnqueueNode) {
  Frontier<2> frontier(start_node);
  ASSERT_NO_FATAL_FAILURE(frontier.EnqueueNode(node1););
  EXPECT_EQ(frontier.GetSize(), 2);
}

TEST_F(FrontierTest, DequeueNode) {
  Frontier<2> frontier(start_node);
  frontier.EnqueueNode(node1);
  frontier.EnqueueNode(node2);
  frontier.EnqueueNode(node3);
  EXPECT_EQ(frontier.GetSize(), 4);

  auto node = frontier.DequeueNode();
  EXPECT_EQ(node->GetAttributes().size(), 2);
  EXPECT_EQ(frontier.GetSize(), 3);
}
