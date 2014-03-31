#include <stdio.h>
#include <iostream>
#include "BotConstants.hpp"
#include "Edge.hpp"
#include "gtest/gtest.h"

using namespace BotConsts;

TEST(Edge, DefaultConstructor)
{
    Edge* edge = new Edge();

    ASSERT_EQ(-1, edge->getFrom());
    ASSERT_EQ(-1, edge->getTo());
    ASSERT_EQ(256, edge->getCost());
    ASSERT_EQ(false, edge->isChecked());
}

TEST(Edge, Cst_with_from_to)
{
    Edge* edge = new Edge(1, 25);

    ASSERT_EQ(1, edge->getFrom());
    ASSERT_EQ(25, edge->getTo());
    ASSERT_EQ(256, edge->getCost());
    ASSERT_EQ(false, edge->isChecked());
}

TEST(Edge, Cst_with_from_to_cost)
{
    Edge* edge = new Edge(1, 25, 33);

    ASSERT_EQ(1, edge->getFrom());
    ASSERT_EQ(25, edge->getTo());
    ASSERT_EQ(33, edge->getCost());
    ASSERT_EQ(false, edge->isChecked());
}

TEST(Edge, Change_cost)
{
    Edge* edge = new Edge(3, 25);

    ASSERT_EQ(256, edge->getCost());
    edge->setCost(10);
    ASSERT_EQ(10, edge->getCost());
}

TEST(Edge, Change_checked)
{
    Edge* edge = new Edge(3, 25, 22);

    ASSERT_EQ(false, edge->isChecked());
    edge->setChecked(true);
    ASSERT_EQ(true, edge->isChecked());
}
