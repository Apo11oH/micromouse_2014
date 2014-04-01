#include <stdio.h>
#include <iostream>
#include "BotConstants.hpp"
#include "Edge.hpp"
#include "Node.hpp"
#include "gtest/gtest.h"

using namespace BotConsts;

TEST(Node, DefaultConstructor)
{
    Node* node = new Node();

    ASSERT_EQ(-1, node->getIndex());
    ASSERT_EQ(256, node->getCost());
    ASSERT_EQ(false, node->isChecked());
    ASSERT_EQ(-1, node->getFrom());
}

TEST(Node, Cnst_with_index)
{
    Node* node = new Node(23);

    ASSERT_EQ(23, node->getIndex());
    ASSERT_EQ(256, node->getCost());
    ASSERT_EQ(false, node->isChecked());
    ASSERT_EQ(-1, node->getFrom());
}

TEST(Node, Cnst_with_index_cost)
{
    Node* node = new Node(23, 22);

    ASSERT_EQ(23, node->getIndex());
    ASSERT_EQ(22, node->getCost());
    ASSERT_EQ(false, node->isChecked());
    ASSERT_EQ(-1, node->getFrom());
}

TEST(Node, Add_edges)
{
    Node* node = new Node(0);

    ASSERT_EQ(0, (node->getEdges()).size());
    node->addEdge(new Edge());
    ASSERT_EQ(1, (node->getEdges()).size());
}

TEST(Node, Change_cost)
{
    Node* node = new Node(0, 33);

    ASSERT_EQ(33, node->getCost());
    node->setCost(34);
    ASSERT_EQ(34, node->getCost());
}

TEST(Node, Change_checked)
{
    Node* node = new Node(0);

    ASSERT_EQ(false, node->isChecked());
    node->setChecked(true);
    ASSERT_EQ(true, node->isChecked());
}

TEST(Node, Change_from)
{
    Node* node = new Node(0);

    ASSERT_EQ(-1, node->getFrom());
    node->setFrom(22);
    ASSERT_EQ(22, node->getFrom());
}

TEST(Node, Wall_default)
{
    Node* node = new Node(0);

    ASSERT_EQ(0, node->getWall(DIR_NORTH));  
    ASSERT_EQ(0, node->getWall(DIR_EAST));  
    ASSERT_EQ(0, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(0, node->getWall(DIR_WEST));  
}

TEST(Node, Wall_set_N_and_E)
{
    Node* node = new Node(0);

    ASSERT_EQ(0, node->getWall(DIR_NORTH));  
    ASSERT_EQ(0, node->getWall(DIR_EAST));  
    ASSERT_EQ(0, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(0, node->getWall(DIR_WEST));  
    node->setWall(1, DIR_NORTH);
    node->setWall(1, DIR_EAST);
    ASSERT_EQ(1, node->getWall(DIR_NORTH));  
    ASSERT_EQ(1, node->getWall(DIR_EAST));  
    ASSERT_EQ(0, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(0, node->getWall(DIR_WEST));  
}

TEST(Node, Wall_set_ALL)
{
    Node* node = new Node(0);

    ASSERT_EQ(0, node->getWall(DIR_NORTH));  
    ASSERT_EQ(0, node->getWall(DIR_EAST));  
    ASSERT_EQ(0, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(0, node->getWall(DIR_WEST));  
    node->setWall(1, DIR_NORTH);
    node->setWall(1, DIR_EAST);
    node->setWall(1, DIR_SOUTH);
    node->setWall(1, DIR_WEST);
    ASSERT_EQ(1, node->getWall(DIR_NORTH));  
    ASSERT_EQ(1, node->getWall(DIR_EAST));  
    ASSERT_EQ(1, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(1, node->getWall(DIR_WEST));  
}

TEST(Node, Wall_set_ALL_reset_N_S)
{
    Node* node = new Node(0);

    ASSERT_EQ(0, node->getWall(DIR_NORTH));  
    ASSERT_EQ(0, node->getWall(DIR_EAST));  
    ASSERT_EQ(0, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(0, node->getWall(DIR_WEST));  
    node->setWall(1, DIR_NORTH);
    node->setWall(1, DIR_EAST);
    node->setWall(1, DIR_SOUTH);
    node->setWall(1, DIR_WEST);
    ASSERT_EQ(1, node->getWall(DIR_NORTH));  
    ASSERT_EQ(1, node->getWall(DIR_EAST));  
    ASSERT_EQ(1, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(1, node->getWall(DIR_WEST));  
    node->setWall(0, DIR_NORTH);
    node->setWall(0, DIR_SOUTH);
    ASSERT_EQ(0, node->getWall(DIR_NORTH));  
    ASSERT_EQ(1, node->getWall(DIR_EAST));  
    ASSERT_EQ(0, node->getWall(DIR_SOUTH));  
    ASSERT_EQ(1, node->getWall(DIR_WEST));  
}

TEST(Node, Wall_pattern_default)
{
    Node* node = new Node(0);
    unsigned pat = 0x00;

    ASSERT_EQ(pat, node->getWallPat());
}

TEST(Node, Wall_pattern_modified)
{
    Node* node = new Node(0);
    unsigned pat = 0x03;

    node->setWall(1, DIR_NORTH);
    node->setWall(1, DIR_EAST);

    ASSERT_EQ(pat, node->getWallPat());
}

TEST(Node, Edges_default)
{
    Node* node = new Node(0);
    ASSERT_EQ(0, (node->getEdges()).size());
}

TEST(Node, Edges_clear)
{
    Node* node = new Node(0);
    node->addEdge(new Edge());
    node->addEdge(new Edge());
    node->addEdge(new Edge());
    ASSERT_EQ(3, (node->getEdges()).size());
    node->clearAllEdges();
    ASSERT_EQ(0, (node->getEdges()).size());
}

TEST(Node, Adding_edges)
{
    Node* node = new Node(0);
    for(int i=0; i<8; i++)
    {
        node->addEdge(new Edge(0, i));
    }
    vector<Edge*> edges = node->getEdges();
    for(int i=0; i<8; i++)
    {
        ASSERT_EQ(i, edges[i]->getTo());
    }
}
