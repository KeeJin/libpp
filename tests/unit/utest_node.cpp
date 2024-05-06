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

TEST(NodeTest, NodeAttributeEquality) {
  NodeAttribute node_attribute_1(1, Dimension("x dimension", 0, 5, 1));
  NodeAttribute node_attribute_2(1, Dimension("x dimension", 0, 5, 1));
  NodeAttribute node_attribute_3(2, Dimension("x dimension", 0, 5, 1));
  NodeAttribute node_attribute_4(1, Dimension("y dimension", 0, 5, 1));

  EXPECT_EQ(node_attribute_1, node_attribute_2);
  EXPECT_NE(node_attribute_1, node_attribute_3);
  EXPECT_NE(node_attribute_1, node_attribute_4);
}

TEST(NodeTest, NodeNeighbours) {
  std::shared_ptr<Node<2>> node_1 = std::make_shared<Node<2>>(
      (NodeAttributes<2>){NodeAttribute(1, Dimension("x dimension", 0, 5, 1)),
                          NodeAttribute(2, Dimension("y dimension", 0, 5, 1))});
  std::shared_ptr<Node<2>> node_2 = std::make_shared<Node<2>>(
      (NodeAttributes<2>){NodeAttribute(2, Dimension("x dimension", 0, 5, 1)),
                          NodeAttribute(3, Dimension("y dimension", 0, 5, 1))});
  std::shared_ptr<Node<2>> node_3 = std::make_shared<Node<2>>(
      (NodeAttributes<2>){NodeAttribute(3, Dimension("x dimension", 0, 5, 1)),
                          NodeAttribute(4, Dimension("y dimension", 0, 5, 1))});
  std::shared_ptr<Node<2>> node_4 = std::make_shared<Node<2>>(
      (NodeAttributes<2>){NodeAttribute(4, Dimension("x dimension", 0, 5, 1)),
                          NodeAttribute(5, Dimension("y dimension", 0, 5, 1))});
  std::shared_ptr<Node<2>> node_5 = std::make_shared<Node<2>>(
      (NodeAttributes<2>){NodeAttribute(5, Dimension("x dimension", 0, 5, 1)),
                          NodeAttribute(4, Dimension("y dimension", 0, 5, 1))});

  node_1->AddNeighbor(node_2);
  EXPECT_TRUE(node_1->IsNeighbour(node_2));
  EXPECT_FALSE(node_1->IsNeighbour(node_3));
  EXPECT_EQ(node_1->GetNeighbours().size(), 1);
  EXPECT_EQ(node_1->GetEdges().size(), 1);

  node_1->AddNeighbor(node_3);
  EXPECT_TRUE(node_1->IsNeighbour(node_2));
  EXPECT_TRUE(node_1->IsNeighbour(node_3));
  EXPECT_EQ(node_1->GetNeighbours().size(), 2);
  EXPECT_EQ(node_1->GetEdges().size(), 2);

  node_2->AddNeighbor(node_4);
  node_2->AddNeighbor(node_5);
  EXPECT_TRUE(node_2->IsNeighbour(node_1));
  EXPECT_FALSE(node_2->IsNeighbour(node_3));
  EXPECT_TRUE(node_2->IsNeighbour(node_4));
  EXPECT_TRUE(node_2->IsNeighbour(node_5));
  EXPECT_EQ(node_2->GetNeighbours().size(), 3);
  EXPECT_EQ(node_2->GetEdges().size(), 3);

  EXPECT_EQ(node_2->GetUnexploredNeighbours().size(), 3);
  node_1->MarkAsExplored();
  EXPECT_EQ(node_2->GetUnexploredNeighbours().size(), 2);
}